package sample;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.collections.ObservableListBase;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import java.sql.*;
import java.sql.Driver;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.DateTimeException;
import java.util.*;


public class Main extends Application {

    public static Stage current;
    public static Stage notice = new Stage();

    @Override
    public void start(Stage primaryStage) throws Exception{
        current = primaryStage;
        primaryStage.setTitle("NTCS");
        notice.setTitle("消息提醒");

        //连接数据库
        ConnectDatebase connect = new ConnectDatebase();
        //设置开启界面
        Menu managemenu = new Menu(connect);
        managemenu.openusermenu();
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}

//界面类
class Menu{

    ConnectDatebase connect;
    int type;//0中转次数最少，1最省时，2最省钱

    public Menu(ConnectDatebase connect) { this.connect =connect; }

    public Menu() { }

    //用户查询路径界面
    public void openusermenu() throws SQLException{
        Button controldatebase = new Button("数据库管理");
        HBox hBox = new HBox(5);
        hBox.setPadding(new Insets(0,0,0,0));
        hBox.setAlignment(Pos.CENTER_RIGHT);
        hBox.getChildren().add(controldatebase);

        TextArea resultdisplay = new TextArea();
        VBox vBox = new VBox(10);
        Label tip = new Label("搜索结果：");
        vBox.getChildren().addAll(tip,resultdisplay);

        ComboBox<String> startcmo = new ComboBox<>();
        ComboBox<String> endcmo = new ComboBox<>();
        VBox usermenu = new VBox(10);
        RadioButton transitbutton = new RadioButton("中转最少");
        RadioButton timebutton = new RadioButton("最省时");
        RadioButton pricebutton = new RadioButton("最省钱");
        Button find = new Button("查找");
        startcmo.setPrefSize(100,30);
        endcmo.setPrefSize(100,30);
        find.setPrefSize(80,30);
        controldatebase.setPrefSize(100,30);
        Label title = new Label("全国交通咨询系统");
        title.setTextFill(Color.BLUE);
        title.setFont(new Font("Times New Roman",30));
        ToggleGroup group = new ToggleGroup();
        HBox paneforradioButtons = new HBox(15);
        //创建一个按钮组
        transitbutton.setToggleGroup(group);
        timebutton.setToggleGroup(group);
        pricebutton.setToggleGroup(group);

        ResultSet result = connect.List_City();
        startcmo.setValue("出发地");
        endcmo.setValue("到达地");
        while (result.next()) {
            startcmo.getItems().add(result.getString("name"));
        }
        paneforradioButtons.getChildren().addAll(transitbutton,timebutton,pricebutton,startcmo,endcmo,find);
        usermenu.setPadding(new Insets(20,20,20,20));
        usermenu.setAlignment(Pos.CENTER);
        usermenu.getChildren().addAll(title,paneforradioButtons,vBox,hBox);

        Main.current.setScene(new Scene(usermenu,800,400));

        startcmo.setOnAction(e->{
            try{
                endcmo.setValue("到达地");
                StringBuilder str = new StringBuilder();
                ResultSet endresult = connect.List_City();
                while (endresult.next())
                {
                    String temp = endresult.getString("name");
                    if(startcmo.getValue().equals(temp))
                        continue;
                    str.append(temp+"\n");
                }
                String[] strlist = str.toString().split("\\n");
                ObservableList<String> end = FXCollections.observableArrayList(strlist);
                endcmo.setItems(end);
            }catch (SQLException ex){
                ex.printStackTrace();
            }
        });

        find.setOnAction(event -> {
            Graph graph = new Graph(connect);
            String start = startcmo.getValue();
            String end = endcmo.getValue();
            if(!transitbutton.isSelected() && !timebutton.isSelected() && !pricebutton.isSelected()){
                new note("请选择查询方式");
                return;
            }
            if (end.equals("到达地"))
            {
                new note("请选择出发地和到达地");
                return;
            }
            if(transitbutton.isSelected()){
                try {
                resultdisplay.setText(graph.BFS(start,end,graph.Create()));
                }catch (SQLException e){
                    e.printStackTrace();
                }catch (ParseException e ){
                    e.printStackTrace();
                }
            }else if(timebutton.isSelected()){
                try {
                    try{
                        resultdisplay.setText(graph.Dijkstratime(start,end,graph.Create()));
                    }catch(ParseException ex){
                        ex.printStackTrace();
                    }
                }catch (SQLException e){
                    e.printStackTrace();
                }
            }
            else {
                try {
                    try{
                        resultdisplay.setText(graph.Dijkstra(start,end,graph.Create()));
                    }catch(ParseException ex){
                        ex.printStackTrace();
                    }

                }catch (SQLException e){
                    e.printStackTrace();
                }
            }
        });

        controldatebase.setOnAction(e->openmanagemenu());


    }

    //管理菜单
    public void openmanagemenu(){
        GridPane managemenu = new GridPane();
        Button citylist = new Button("查询城市信息");
        Button cityadd = new Button("添加一个城市");
        Button citydelete = new Button("删除一个城市");
        Button citymodify = new Button("修改城市信息");
        Button timetablelist = new Button("时刻表");
        Button timetableadd = new Button("添加车次");
        Button timetabledelete = new Button("删除车次");
        //Button timetablemodify = new Button("修改车次");
        Button ret = new Button("返回");
        citylist.setPrefSize(100,30);
        cityadd.setPrefSize(100,30);
        citydelete.setPrefSize(100,30);
        citymodify.setPrefSize(100,30);
        timetablelist.setPrefSize(100,30);
        timetableadd.setPrefSize(100,30);
        timetabledelete.setPrefSize(100,30);
        //timetablemodify.setPrefSize(100,30);
        ret.setPrefSize(100,30);
        managemenu.setAlignment(Pos.CENTER);
        managemenu.setHgap(10);
        managemenu.setVgap(10);
        managemenu.addColumn(0,citylist,cityadd,citydelete,citymodify,
                timetablelist,timetableadd,timetabledelete,ret);
        Main.current.setScene(new Scene(managemenu,800,400));
        //城市的增删改查
        cityadd.setOnAction(e->cityadd());
        citydelete.setOnAction(e->citydelete());
        citymodify.setOnAction(e->citymodify());
        citylist.setOnAction(e->{
            try{
                cityfind();
            }catch (SQLException ex){
                ex.printStackTrace();
            }
        });
        //时刻表的增删改查
        timetableadd.setOnAction(e->routeadd());
        timetabledelete.setOnAction(e->routedelete());
        timetablelist.setOnAction(e->{
            try{
                routelist();
            }catch (SQLException ex){
                ex.printStackTrace();
            }
        });

        //返回搜索界面
        ret.setOnAction(e->{
            try{
                openusermenu();
            }catch (SQLException ex){
                ex.printStackTrace();
            }
        });
    }

    public void cityfind() throws SQLException {

        HashMap<String, String> citymap = new HashMap<>();
        ComboBox<String> citycmo = new ComboBox<>();
        ResultSet result = connect.List_City();
        citycmo.setValue("选择城市");
        while (result.next()) {
            citycmo.getItems().add(result.getString("name"));
            citymap.put(result.getString("name"), result.getString("brief"));
        }
        Label tip = new Label("城市简介：");
        TextArea brief = new TextArea();
        GridPane cityfindui = new GridPane();
        cityfindui.setHgap(10);
        cityfindui.setVgap(10);
        cityfindui.setAlignment(Pos.CENTER);
        Button find = new Button("查询");
        Button ret = new Button("返回");
        cityfindui.add(citycmo, 0, 1);
        cityfindui.add(tip, 1, 0);
        cityfindui.add(brief, 1, 1);
        cityfindui.add(find, 1, 2);
        cityfindui.add(ret, 2, 2);
        Main.current.setScene(new Scene(cityfindui, 800, 400));

        ret.setOnAction(e -> openmanagemenu());

        find.setOnAction(e -> brief.setText(citymap.get(citycmo.getValue())));
    }

    public void cityadd(){
        GridPane cityaddui = new GridPane();
        Label name = new Label("请输入要添加的城市名称：");
        Label brief = new Label("请输入该城市的简介：");
        TextField cityname = new TextField();
        TextArea citybrief = new TextArea();
        Button add = new Button("添加");
        Button ret = new Button("返回");
        cityaddui.setAlignment(Pos.CENTER);
        cityaddui.setHgap(20);
        cityaddui.setVgap(20);
        cityaddui.add(name,0,0);
        cityaddui.add(brief,0,1);
        cityaddui.add(cityname,1,0);
        cityaddui.add(citybrief,1,1);
        cityaddui.add(add,1,2);
        cityaddui.add(ret,2,2);
        Main.current.setScene(new Scene(cityaddui,800,400));

        ret.setOnAction(e->openmanagemenu());

        add.setOnAction(e->{
            City city = new City();
            city.name = cityname.getText();
            city.brief = citybrief.getText();
            if (connect.Cityisexist(city)){
                new note("该城市已经被添加");
            }else {
                if (connect.Add_City(city))
                    new note("添加成功");
                else
                    new note("添加失败");
            }
        });
    }

    public void citydelete(){
        GridPane citydeleteui = new GridPane();
        Label name = new Label("输入要删除的城市名称：");
        TextField cityname = new TextField();
        Button modify = new Button("删除");
        Button ret = new Button("返回");
        citydeleteui.setAlignment(Pos.CENTER);
        citydeleteui.setHgap(20);
        citydeleteui.setVgap(20);
        citydeleteui.add(name,0,0);
        citydeleteui.add(cityname,1,0);
        citydeleteui.add(modify,1,1);
        citydeleteui.add(ret,2,1);
        Main.current.setScene(new Scene(citydeleteui,800,400));

        ret.setOnAction(e->openmanagemenu());

        modify.setOnAction(e->{
            City city = new City();
            city.name = cityname.getText();
            if (!connect.Cityisexist(city)){
                new note("要删除城市不存在");
            }else {
                if (connect.Delete_City(city))
                    new note("删除成功");
                else
                    new note("删除失败");
            }
        });
    }

    public void citymodify(){
        GridPane citymodifyui = new GridPane();
        Label name = new Label("输入要修改的城市名称：");
        Label brief = new Label("请修改该城市的简介：");
        TextField cityname = new TextField();
        TextArea citybrief = new TextArea();
        Button add = new Button("修改");
        Button ret = new Button("返回");
        citymodifyui.setAlignment(Pos.CENTER);
        citymodifyui.setHgap(20);
        citymodifyui.setVgap(20);
        citymodifyui.add(name,0,0);
        citymodifyui.add(cityname,1,0);
        citymodifyui.add(brief,0,1);
        citymodifyui.add(citybrief,1,1);
        citymodifyui.add(add,1,2);
        citymodifyui.add(ret,2,2);
        Main.current.setScene(new Scene(citymodifyui,800,400));

        ret.setOnAction(e->openmanagemenu());

        add.setOnAction(e->{
            City city = new City();
            city.name = cityname.getText();
            city.brief = citybrief.getText();
            if (!connect.Cityisexist(city)){
                new note("要修改信息的城市不存在");
            }else {
                if (connect.Modify_City(city))
                    new note("修改成功");
                else
                    new note("修改失败");
            }
        });
    }

    //------
    //分页显示时刻表
    public void routelist() throws SQLException{
        StringBuilder tempresult = new StringBuilder();
        ResultSet result = connect.List_Route();
        while(result.next())
        {
            tempresult.append(String.format("出发地： %-30s\n到达地： %-30s\n距离：  %-10.2f千米\n列车类型：%-20s\n车次：  %-20s\n票价：  %-10.2f\n出发时间："
                    ,result.getString("start"),result.getString("end"),
                    result.getDouble("distance"),result.getString("vehicle"),
                    result.getString("vehicle_number"),result.getDouble("price"))
                    +result.getTimestamp("depart_time")+"\n到达时间："+result.getTimestamp("arrive_time")+"pre\nnext");
        }
        String  temp = tempresult.toString();
        String[] textcontent = temp.split("pre\\nnext");

        Pagination pagination;
        pagination = new Pagination(textcontent.length, 0);
        pagination.setPageFactory((Integer pageIndex) -> {
            if (pageIndex >= textcontent.length) {
                return null;
            } else {
                return createPage(pageIndex,textcontent);
            }
        });
        VBox routelistui = new VBox(20);
        routelistui.setPadding(new Insets(20,20,20,20));
        Label title = new Label("列车时刻表");
        title.setFont(new Font("Times New Roman",24));
        Button ret = new Button("返回");
        routelistui.setAlignment(Pos.CENTER);
        routelistui.getChildren().add(title);
        routelistui.getChildren().add(pagination);
        routelistui.getChildren().add(ret);
        Main.current.setScene(new Scene(routelistui,800,400));

        ret.setOnAction(e->openmanagemenu());
    }
    public int itemsPerPage() {
        return 1;
    }
    public VBox createPage(int pageIndex,String[] textcontent) {
        VBox box = new VBox(5);
        int page = pageIndex * itemsPerPage();
        for (int i = page; i < page + itemsPerPage(); i++) {
            TextArea text = new TextArea();
            text.setWrapText(true);
            text.setText(textcontent[i]);
            box.getChildren().add(text);
        }
        return box;
    }
    //------
    public void routeadd(){{
        GridPane routeaddui = new GridPane();
        routeaddui.setHgap(10);
        routeaddui.setVgap(10);
        routeaddui.setAlignment(Pos.CENTER);
        Label start = new Label("出发地：");
        Label end = new Label("到达地：");
        Label distance = new Label("距离：");
        Label vehicle = new Label("列车种类：");
        Label vehicle_number = new Label("车次号：");
        Label depart_time = new Label("发车时间：");
        Label arrive_time = new Label("到达时间：");
        Label price = new Label("票价：");
        Button add = new Button("添加");
        Button ret = new Button("返回");
        TextField startfield = new TextField();
        TextField endfield = new TextField();
        TextField distancefield = new TextField();
        ComboBox<String> vehiclecom = new ComboBox<>();
        vehiclecom.setValue("列车类型");
        vehiclecom.getItems().addAll("高铁","动车","直达","特快");
        TextField vehicle_numberfield = new TextField();
        TextField depart_timefield = new TextField();
        TextField arrive_timefield = new TextField();
        Label depart_timefieldtip = new Label("(yyyy-MM-dd HH:mm:ss)");
        Label arrive_timefieldtip = new Label("(yyyy-MM-dd HH:mm:ss)");
        TextField pricefield = new TextField();
        routeaddui.addRow(1,start,startfield);
        routeaddui.addRow(2,end,endfield);
        routeaddui.addRow(3,distance,distancefield);
        routeaddui.addRow(4,vehicle,vehiclecom);
        routeaddui.addRow(5,vehicle_number,vehicle_numberfield);
        routeaddui.addRow(6,depart_time,depart_timefield,depart_timefieldtip);
        routeaddui.addRow(7,arrive_time,arrive_timefield,arrive_timefieldtip);
        routeaddui.addRow(8,price,pricefield);
        routeaddui.add(add,1,9);
        routeaddui.add(ret,2,9);
        Main.current.setScene(new Scene(routeaddui,800,400));

        ret.setOnAction(e->openmanagemenu());

        add.setOnAction(e->{
            try {
                Timetable route = new Timetable();
                City city = new City();
                route.start = startfield.getText();
                route.end = endfield.getText();
                route.distance = Double.parseDouble(distancefield.getText());
                route.vehicle = vehiclecom.getValue();
                route.vehicle_number = vehicle_numberfield.getText();
                route.depart_time = Time.DateToTimestamp(depart_timefield.getText());
                route.arrive_time = Time.DateToTimestamp(arrive_timefield.getText());
                route.price = Double.parseDouble(pricefield.getText());

                city.name = route.start;
                if(!connect.Cityisexist(city))
                    new note("出发地不存在");
                else{
                    city.name = route.end;
                    if(!connect.Cityisexist(city))
                        new note("目的地不存在");
                    else{
                        if (connect.Routeisexist(route)){
                            new note("该列车已被占用");
                        }else{
                            if(connect.Add_Route(route))
                                new note("添加成功");
                            else
                                new note("添加失败");
                        }
                    }
                }
            }catch (ParseException ex){
                new note("输入错误");
            }
        });
    }

    }

    public void routedelete() {
        GridPane routedeleteui = new GridPane();
        Label name = new Label("输入要删除的车次：");
        TextField vehicle_number = new TextField();
        Button delete = new Button("删除");
        Button ret = new Button("返回");
        routedeleteui.setAlignment(Pos.CENTER);
        routedeleteui.setHgap(20);
        routedeleteui.setVgap(20);
        routedeleteui.add(name,0,0);
        routedeleteui.add(vehicle_number,1,0);
        routedeleteui.add(delete,1,1);
        routedeleteui.add(ret,2,1);
        Main.current.setScene(new Scene(routedeleteui,800,400));

        ret.setOnAction(e->openmanagemenu());

        delete.setOnAction(e->{
            Timetable route = new Timetable();
            route.vehicle_number = vehicle_number.getText();
            if(!connect.Routeisexist(route)){
                new note("要删除的车次不存在");
            }else{
                try{
                if(connect.Delete_Route(route))
                    new note("删除成功");
                else
                    new note("删除失败");
                }catch (SQLException ex){
                    ex.printStackTrace();
                }
            }
        });
    }
}

//消息提醒
class note{

    public note(String content){
        Label tip = new Label(content);
        GridPane gridPane = new GridPane();
        gridPane.setAlignment(Pos.CENTER);
        gridPane.setHgap(10);
        gridPane.setVgap(10);
        Button ok = new Button("确定");
        gridPane.add(tip,0,0);
        gridPane.add(ok,1,1);
        Main.notice.setScene(new Scene(gridPane,200,100));
        Main.notice.show();

        ok.setOnAction(e->{
            Main.notice.close();
        });


    }

    public note(){}
}

//MySQL
class ConnectDatebase{
    String url = "jdbc:mysql://localhost:3306/NTCS?useUnicode=true&characterEncoding=utf-8&useSSL=false";
    String user = "root";
    String password = "LM19980108!@";
    Connection conn = null;
    SQLException ex = null;
    PreparedStatement stmt ;
    ResultSet result;
    int citynum = 0;//初始化城市个数
    int routenum = 0;//初始化路线数

    public ConnectDatebase(){
        //注册Driver操作对象
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            throw new RuntimeException("找不到指定的类");
        }

        //连接MySQL
        try {
            System.out.println("start");
            conn = DriverManager.getConnection(url, user, password);

            if(!conn.isClosed()){
                System.out.println("Succeeded connecting to the Database!");
            }
            getnum();
        }
        //数据库连接失败异常处理
        catch(SQLException e) {
            e.printStackTrace();
        }catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void close() throws SQLException{
        conn.close();
        System.out.println("connecting is close!");
    }

    //获取城市个数和路线数
    public void getnum() throws SQLException{
        stmt= conn.prepareStatement("SELECT count(*) totalCount FROM City");
        result = stmt.executeQuery();
        if(result.next()){
            citynum = result.getInt("totalCount");
        }
        stmt= conn.prepareStatement("SELECT count(*) totalCount FROM Timetable");
        result = stmt.executeQuery();
        if(result.next()){
            routenum = result.getInt("totalCount");
        }
    }

    //添加线路
    public boolean Add_Route(Timetable route){
        try{
            //后面的占位符一个也不能少，同样一个也不能多
            stmt = conn.prepareStatement(
               "INSERT INTO Timetable (start,end,distance,vehicle,vehicle_number,depart_time,arrive_time,price)" +
                       "VALUES (?,?,?,?,?,?,?,?)");
            stmt.setString(1,route.start);
            stmt.setString(2,route.end);
            stmt.setDouble(3,route.distance);
            stmt.setString(4,route.vehicle);
            stmt.setString(5,route.vehicle_number);
            stmt.setTimestamp(6,route.depart_time);
            stmt.setTimestamp(7,route.arrive_time);
            stmt.setDouble(8,route.price);
            stmt.execute();
            return true;
        }catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //城市是否存在
    public boolean Routeisexist(Timetable route) {
        try{
            stmt = conn.prepareStatement(
                    "SELECT * FROM Timetable WHERE vehicle_number = ?");
            stmt.setString(1,route.vehicle_number);
            result = stmt.executeQuery();
            if(result.next())
                return true;
            else
                return false;
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //删除路线
    public boolean Delete_Route(Timetable route) throws SQLException{
        try{
            stmt = conn.prepareStatement(
                    "DELETE FROM Timetable where vehicle_number = ?");
            stmt.setString(1,route.vehicle_number);
            stmt.execute();
            return true;
        }catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //修改路线

    //获取发车时间获取时刻表
    public ResultSet List_Route() throws SQLException{
        stmt = conn.prepareStatement("SELECT * FROM Timetable ORDER BY depart_time");
        return stmt.executeQuery();
    }

    //添加城市
    public boolean Add_City(City city) {
        try{
            stmt = conn.prepareStatement(
                "INSERT INTO City (name,brief) VALUES (?,?)");
            stmt.setString(1,city.name);
            stmt.setString(2,city.brief);
            stmt.execute();
            return true;
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //城市是否存在
    public boolean Cityisexist(City city) {
        try{
            stmt = conn.prepareStatement(
                    "SELECT * FROM City WHERE name = ?");
            stmt.setString(1,city.name);
            result = stmt.executeQuery();
            if(result.next())
                return true;
            else
                return false;
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //删除城市
    public boolean Delete_City(City city){
        try{
            stmt = conn.prepareStatement(
                    "DELETE FROM City WHERE name = ?");
            stmt.setString(1,city.name);
            stmt.execute();
            return true;
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //修改城市
    public boolean Modify_City(City city){
        try{
            stmt = conn.prepareStatement(
                    "UPDATE City SET brief = ? WHERE name = ?");
            stmt.setString(1,city.brief);
            stmt.setString(2,city.name);
            stmt.execute();
            return true;
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //获取字母序获取城市列表
    public ResultSet List_City() throws SQLException{
            stmt = conn.prepareStatement("SELECT * FROM City ORDER BY name");
            return stmt.executeQuery();
    }

}

//城市类
class City{
                          //长度
    String name;          //30
    String brief;         //255

    City(){}
}

//时刻表类
class Timetable{
                          //长度
    String start;         //30
    String end;           //30
    double distance;
    String vehicle;       //20
    String vehicle_number;//20
    Timestamp depart_time;
    Timestamp arrive_time;
    double price;

    Timetable(){}
};

//顶点类
class VertexNode{
    City city = new City();
    LinkedList<ArcNode> list = new LinkedList();

    VertexNode() {}

    @Override
    public String toString(){
        System.out.print(city.name);
        for(int i=0;i<list.size();i++){
            System.out.print("    "+list.get(i).adjvex+"  "+list.get(i).weight);
        }
        System.out.println();
        return city.name + list;
    }
}

//边类
class ArcNode{
    int adjvex;
    double weight;
    double distance;
    String vehicle;
    String vehicle_number;
    Timestamp depart_time;
    Timestamp arrive_time;
    ArcNode() {}
}

//图的操作
class Graph {

    ConnectDatebase connect;

    Graph(){}

    Graph(ConnectDatebase connect) { this.connect = connect; }

    public VertexNode[] Create() throws java.sql.SQLException {

        int n = connect.citynum;
        //建立顶点数组并初始化
        VertexNode[] Vertexlist = new VertexNode[n+1];

        for (int i = 1; i <= n; i++)
            Vertexlist[i] = new VertexNode();

        //建立顶点集
        int i = 1;
        connect.stmt = connect.conn.prepareStatement("SELECT name FROM City ");
        connect.result = connect.stmt.executeQuery();
        while(connect.result.next()){
            Vertexlist[i].city.name = connect.result.getString("name");
            i++;
        }

        //建立边集
        connect.stmt = connect.conn.prepareStatement("SELECT * FROM Timetable");
        connect.result = connect.stmt.executeQuery();
        while(connect.result.next()){
            String start = connect.result.getString("start");
            String end = connect.result.getString("end");
            double weight = connect.result.getDouble("price");
            //System.out.println(start+"  "+end+"  "+weight);
            //查询对应的下标
            int x = Locate(start,Vertexlist);
            int y = Locate(end,Vertexlist);
            //添加边关系
            ArcNode node = new ArcNode();
            node.adjvex = y;
            node.weight = weight;
            node.depart_time = connect.result.getTimestamp("depart_time");
            node.arrive_time = connect.result.getTimestamp("arrive_time");
            node.distance = connect.result.getDouble("distance");
            node.vehicle = connect.result.getString("vehicle");
            node.vehicle_number = connect.result.getString("vehicle_number");
            Vertexlist[x].list.add(node);
        }

        for (int k = 1; k <= n; k++){
            System.out.print(k+" ");
            Vertexlist[k].toString();
        }
        return Vertexlist;
    }

    public int Locate(String name,VertexNode[] Vertexlist) {
        for (int i = 1; i <= connect.citynum; i++) {
            //查找到对应的位置
            if (name.equals(Vertexlist[i].city.name))
                return i;
        }
        //没有找到
        return -1;
    }

    //最省时
    public String Dijkstratime(String start,String end,VertexNode[] Vertexlist) throws ParseException{

        int arraymax = connect.citynum+1;
        //获取起点终点的位置
        int startindex = Locate(start,Vertexlist);
        int endindex = Locate(end,Vertexlist);

        //初始化
        dijnode[] nodelist = new dijnode[arraymax];
        for(int i=1;i<=connect.citynum;i++){ nodelist[i] = new dijnode(); }

        Stack<Integer> stack = new Stack<>();
        nodelist[startindex].weight = 0;
        stack.push(startindex);

        while(!stack.empty()){
            double min = Double.MAX_VALUE;
            int minindex = -1;
            int current = stack.pop();
            nodelist[current].visit = true;

            for(int i=0;i<Vertexlist[current].list.size();i++){
                if(!Time.timeisbefore(nodelist[current].time,Vertexlist[current].list.get(i).depart_time))
                    continue;

                int j = Vertexlist[current].list.get(i).adjvex;
                double temp ;
                //获取时间差
                if(0 == Time.timedifference(nodelist[current].time,Time.DateToTimestamp("0000-00-00 00:00:00")))
                {
                    temp = Time.timedifference(Vertexlist[current].list.get(i).depart_time,Vertexlist[current].list.get(i).arrive_time);
                }else{
                    temp = Time.timedifference(nodelist[current].time,Vertexlist[current].list.get(i).arrive_time);
                }
                //从当前结点找能到达的最近的没被访问过的结点
                if(!nodelist[j].visit && min > temp) {
                    minindex = j;
                }
                //原来没有路径或者现在有更短的路径
                if(!nodelist[j].visit && nodelist[j].weight > nodelist[current].weight + temp)
                {
                    nodelist[j].weight = nodelist[current].weight + temp;
                    nodelist[j].path.clear();
                    nodelist[j].time = Vertexlist[current].list.get(i).arrive_time;
                    for(int k = 0;k < nodelist[current].path.size();k++) {
                        nodelist[j].path.add(nodelist[current].path.get(k)); }
                    nodelist[j].path.add(Vertexlist[current].list.get(i));
                }
                if(minindex > -1){
                    stack.push(minindex);
                }
            }
        }

        StringBuilder result = new StringBuilder();
        result.append("时间最短的方式：\n"+Vertexlist[startindex].city.name  );
        for(int i=0;i<nodelist[endindex].path.size();i++){
            ArcNode temp = nodelist[endindex].path.get(i);
            result.append("--"+temp.vehicle+":"+temp.vehicle_number +"-->"+Vertexlist[temp.adjvex].city.name);
        }
        result.append("\n所需时间:  "+nodelist[endindex].weight+"小时");

        if(nodelist[endindex].weight != Double.MAX_VALUE)
            return result.toString();
        else
            return "无法到达";
    }

    //最省钱
    public String Dijkstra(String start,String end,VertexNode[] Vertexlist) throws ParseException{

        int arraymax = connect.citynum+1;
        //获取起点终点的位置
        int startindex = Locate(start,Vertexlist);
        int endindex = Locate(end,Vertexlist);

        //初始化
        dijnode[] nodelist = new dijnode[arraymax];
        for(int i=1;i<=connect.citynum;i++){ nodelist[i] = new dijnode(); }

        Stack<Integer> stack = new Stack<>();
        nodelist[startindex].weight = 0;
        stack.push(startindex);

        while(!stack.empty()){
            double min = Double.MAX_VALUE;
            int minindex = -1;
            int current = stack.pop();
            nodelist[current].visit = true;

            for(int i=0;i<Vertexlist[current].list.size();i++){
                int j = Vertexlist[current].list.get(i).adjvex;
                double temp =  Vertexlist[current].list.get(i).weight;

                if(!Time.timeisbefore(nodelist[current].time,Vertexlist[current].list.get(i).depart_time))
                    continue;
                //从当前结点找能到达的最近的没被访问过的结点
                if(!nodelist[j].visit && min > temp) {
                    minindex = j;
                }

                //原来没有路径或者现在有更短的路径
                if(!nodelist[j].visit && nodelist[j].weight > nodelist[current].weight + temp){
                    nodelist[j].weight = nodelist[current].weight + temp;
                    //路径的继承
                    nodelist[j].path.clear();
                    for(int t = 0;t < nodelist[current].path.size();t++) {
                        nodelist[j].path.add(nodelist[current].path.get(t));
                    }
                    nodelist[j].path.add(Vertexlist[current].list.get(i));
                    //时间更新为到达最后一站的时间
                    nodelist[j].time = Vertexlist[current].list.get(i).arrive_time;
                }
                if(minindex > -1){
                    stack.push(minindex);
                }
            }
        }


        StringBuilder result = new StringBuilder();
        result.append("最省钱的方式：\n"+Vertexlist[startindex].city.name  );
        for(int i=0;i<nodelist[endindex].path.size();i++){
            ArcNode temp = nodelist[endindex].path.get(i);
            result.append("--"+temp.vehicle+":"+temp.vehicle_number +"-->"+Vertexlist[temp.adjvex].city.name);
        }
        result.append("\n票价:  "+nodelist[endindex].weight);
        if(nodelist[endindex].weight != Double.MAX_VALUE)
            return result.toString();
        else
            return "无法到达";
    }

    //最少中转次数
    public String BFS(String start,String end,VertexNode[] Vertexlist) throws ParseException{

        boolean flag = false;
        int count = 0;
        StringBuilder result = new StringBuilder();
        int arraymax = connect.citynum+1;
        //获取起点终点的位置
        int startindex = Locate(start,Vertexlist);
        int endindex = Locate(end,Vertexlist);

        Queue<node> queue = new LinkedList<>();
        boolean[] visit = new boolean[arraymax];
        for(int i=1;i<=connect.citynum;i++){ visit[i] = false; }

        node curnode = new node();
        curnode.count = 0;
        curnode.index = startindex;

        visit[startindex] = true;
        queue.offer(curnode);
        while(!queue.isEmpty()){
            curnode = queue.poll();
            for(int i=0;i<Vertexlist[curnode.index].list.size();i++){
                int j = Vertexlist[curnode.index].list.get(i).adjvex;
                //时间不符合
                if(!Time.timeisbefore(curnode.time,Vertexlist[curnode.index].list.get(i).depart_time))
                    continue;

                if(!visit[j]){
                    visit[j] = true;
                    //已经找到该点
                    if(j == endindex){
                        flag = true;
                        count = curnode.count;//能够直达就不用中转
                        curnode.queue.offer(Vertexlist[curnode.index].list.get(i));
                        result.append("最少中转次数：\n");
                        result.append(Vertexlist[startindex].city.name);
                        while(!curnode.queue.isEmpty()){
                            ArcNode temp = curnode.queue.poll();
                            result.append("--"+temp.vehicle+":"+temp.vehicle_number+"-->"+Vertexlist[temp.adjvex].city.name);
                        }
                        result.append("\n中转"+count+" 次");
                    }
                    node nextnode = new node();
                    nextnode.index = j;
                    nextnode.count = curnode.count+1;
                    while(!curnode.queue.isEmpty()){
                        nextnode.queue.offer(curnode.queue.poll());
                    }
                    nextnode.queue.offer(Vertexlist[curnode.index].list.get(i));
                    nextnode.time = Vertexlist[curnode.index].list.get(i).arrive_time;
                    queue.offer(nextnode);
                }
            }
        }
        if(flag)
            return result.toString();
        else
            return "无法到达";
    }

}

//Dijkstra所用的节点
class dijnode{
    double weight ;
    boolean visit ;
    LinkedList <ArcNode> path ;
    Timestamp time ;

    public dijnode() throws ParseException{
        weight = Double.MAX_VALUE;
        visit = false;
        path = new LinkedList<ArcNode>();
        time = Time.DateToTimestamp("0000-00-00 00:00:00");
    }
}

//最少中转次数的存储数据的节点
class node{
    int index;
    int count;
    Queue<ArcNode> queue = new LinkedList<>();
    Timestamp time;

    public node() throws  ParseException{
        time = Time.DateToTimestamp("0000-00-00 00:00:00");
    }
}

//关于时间的比较和转化
class Time{

    //计算两个日期的时间差(单位为小时)
    public static double timedifference(Timestamp start,Timestamp end){
        return (end.getTime()-start.getTime())*1.0/(1000*60*60);
    }

    //比较两个时间的先后
    public static boolean timeisbefore(Timestamp a,Timestamp b){
        if(a.before(b))
            return true;
        return false;
    }

    //String转化为Timestamp
    public static Timestamp DateToTimestamp(String datestring) throws ParseException{
        //HH是24时制，hh是12小时，会把12解析为00
        SimpleDateFormat df =new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        java.util.Date date = df.parse(datestring);
        return new Timestamp(date.getTime());
    }
}













