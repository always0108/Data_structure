package sample;

import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
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

import javax.swing.text.DefaultEditorKit;
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

        //Scanner input = new Scanner(System.in);
        ConnectDatebase connect = new ConnectDatebase();
        //Usermenu usermenu = new Usermenu(connect);
        //usermenu.start();

        Managemenu managemenu = new Managemenu(connect);
        managemenu.openmanagemenu();

        primaryStage.setTitle("NTCS");
        notice.setTitle("消息提醒");
        primaryStage.show();




        /*Time time = new Time();
        Timetable route = new Timetable();
        route.start = "北京";
        route.end = "哈尔滨";
        route.distance = 1000;
        route.vehicle = "火车";
        route.vehicle_number = "k24";
        route.price = 200;
        route.depart_time = time.DateToTimestamp("2018-01-04 08:00:00");
        route.arrive_time = time.DateToTimestamp("2018-01-04 16:00:00");
        //connect.Add_Route(route);*/

        /*City city = new City();
        city.name = input.next();
        city.brief = input.next();
        //connect.Add_City(city);
        connect.Modify_City(city);
        connect.close();*/


    }

    public static void main(String[] args) {
        launch(args);
    }
}

class Usermenu{

    ConnectDatebase connect;

    int type;//0中转次数最少，1最省时，2最省钱
    TextArea resultdisplay = new TextArea();
    Button controldatebase = new Button("数据库管理");

    public Usermenu(ConnectDatebase connect)
    {
        this.connect =connect;
    }

    public Usermenu() { }



    public void start() throws SQLException{


        ComboBox<String> startcmo = new ComboBox<>();
        ComboBox<String> endcmo = new ComboBox<>();
        BorderPane pane = new BorderPane();
        RadioButton transitbutton = new RadioButton("中转最少");
        RadioButton timebutton = new RadioButton("最省时");
        RadioButton pricebutton = new RadioButton("最省钱");
        Button find = new Button("查找");
        Label title = new Label("全国交通咨询系统");
        ToggleGroup group = new ToggleGroup();
        HBox paneforradioButtons = new HBox(20);
        //创建一个按钮组
        transitbutton.setToggleGroup(group);
        timebutton.setToggleGroup(group);
        pricebutton.setToggleGroup(group);

        ResultSet result = connect.List_City();
        startcmo.setValue("出发地");
        endcmo.setValue("到达地");
        while (result.next())
        {
            startcmo.getItems().add(result.getString("name"));
            endcmo.getItems().add(result.getString("name"));
        }
        paneforradioButtons.setPadding(new Insets(40,20,20,20));
        paneforradioButtons.getChildren().addAll(transitbutton,timebutton,pricebutton,startcmo,endcmo,find);
        pane.setTop(paneforradioButtons);
        pane.setLeft(getresult());
        pane.setBottom(getcontrol());


        find.setOnAction(event -> {
            if(transitbutton.isSelected())
                type = 0;
            else if(timebutton.isSelected())
                type = 1;
            else
                type = 2;
            String strat = startcmo.getValue();
            String end = endcmo.getValue();

            System.out.println(strat + " " + end +" " + type);
            try {
                Graph graph = new Graph(connect);
                resultdisplay.setText(graph.Dijkstra(strat,end));
            }catch (SQLException e){
                e.printStackTrace();
            }

        });
    }

    private VBox getresult(){
        VBox vBox = new VBox();
        vBox.setPadding(new Insets(20,20,20,20));
        Label tip = new Label("搜索结果：");
        vBox.getChildren().addAll(tip,resultdisplay);
        return vBox;
    }


    private HBox getcontrol(){
        HBox hBox = new HBox();
        hBox.setPadding(new Insets(20,20,20,20));
        hBox.getChildren().add(controldatebase);
        return  hBox;
    }
}
class Managemenu{

    ConnectDatebase connect;

    public Managemenu(ConnectDatebase connect)
    {
        this.connect =connect;
    }

    public Managemenu() { }


    public void openmanagemenu(){
        GridPane managemenu = new GridPane();
        Button citylist = new Button("查询城市信息");
        Button cityadd = new Button("添加一个城市");
        Button citydelete = new Button("删除一个城市");
        Button citymodify = new Button("修改城市信息");
        Button timetablelist = new Button("时刻表");
        Button timetableadd = new Button("添加车次");
        Button timetabledelete = new Button("删除车次");
        Button timetablemodify = new Button("修改车次");
        citylist.setPrefSize(100,30);
        cityadd.setPrefSize(100,30);
        citydelete.setPrefSize(100,30);
        citymodify.setPrefSize(100,30);
        timetablelist.setPrefSize(100,30);
        timetableadd.setPrefSize(100,30);
        timetabledelete.setPrefSize(100,30);
        timetablemodify.setPrefSize(100,30);
        managemenu.setAlignment(Pos.CENTER);
        managemenu.setHgap(20);
        managemenu.setVgap(20);
        managemenu.addColumn(0,citylist,cityadd,citydelete,citymodify,
                timetablelist,timetableadd,timetabledelete,timetablemodify);
        Main.current.setScene(new Scene(managemenu,800,400));

        citylist.setOnAction(e->{
            try{
                cityfind();
            }catch (SQLException ex){
                ex.printStackTrace();
            }
        });
        cityadd.setOnAction(e->cityadd());
        citydelete.setOnAction(e->citydelete());
        citymodify.setOnAction(e->citymodify());
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

    public void routeadd(){{
        GridPane routeaddui = new GridPane();
        Label start = new Label("出发地：");
        Label end = new Label("到达地：");
        Label ditance = new Label("距离：");
        Label vehicle = new Label("列车种类：");
        Label vehicle_number = new Label("车次号：");
        Label depart_time = new Label("发车时间：");
        Label arrive_time = new Label("到达时间：");
        Label price = new Label("票价");
        Button find = new Button("添加");
        Button ret = new Button("返回");
        TextField startfield = new TextField();
        TextField endfield = new TextField();
        TextField distancefield = new TextField();
        ComboBox<String> vehiclecom = new ComboBox<>();
        vehiclecom.getItems().addAll("高铁","动车","直达","特快");
        TextField vehicle_numberfield = new TextField();
        TextField pricefield = new TextField();





    }

    }
}

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
            stmt = conn.prepareStatement(
               "INSERT INTO Timetable(start,end,distance,vehicle,vehicle_number,depart_time,arrive_time,price)" +
                       "VALUES (?,?,?,?,?,?,?,?,?)");
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
            return false;
        }
    }

    //删除路线
    public boolean Delete_Route(Timetable route) throws SQLException{
        try{
            stmt = conn.prepareStatement(
                    "DELETE FROM Timetable where vehicle_number = ? and depart_time = ?");
            stmt.setString(1,route.vehicle_number);
            stmt.setTimestamp(2,route.depart_time);
            stmt.execute();
            return true;
        }catch (SQLException e){
            e.printStackTrace();
            return false;
        }
    }

    //修改路线

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

    //获取城市列表
    public ResultSet List_City() throws SQLException{
            stmt = conn.prepareStatement("SELECT * FROM City");
            return stmt.executeQuery();
    }


}



class User{
                         //长度
    String name;         //20
    String password;     //20
    String type;         //10
    String question;     //50
    String answer;       //20

    User(){}
}

class City{
                          //长度
    String name;          //30
    String brief;         //255

    City(){}
}

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


//顶点
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

//边集
class ArcNode{
    int adjvex;
    double weight;
    Timestamp depart_time;
    Timestamp arrive_time;
    ArcNode() {}
}

class Graph {

    ConnectDatebase connect;
    VertexNode[] Vertexlist;

    Graph(){}

    Graph(ConnectDatebase connect) throws java.sql.SQLException{
        this.connect = connect;
        Vertexlist = Create();
    }

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
            //System.out.println(Vertexlist[i].city.name);
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
            int x = Locate(start);
            int y = Locate(end);
            //添加边关系
            ArcNode node = new ArcNode();
            node.adjvex = y;
            node.weight = weight;
            Vertexlist[x].list.add(node);
        }
        for (int k = 1; k <= n; k++){
            System.out.print(k+" ");
            Vertexlist[k].toString();
        }
        return Vertexlist;
    }

    public int Locate(String name) {
        for (int i = 1; i <= connect.citynum; i++) {
            //查找到对应的位置
            if (name.equals(Vertexlist[i].city.name))
                return i;
        }
        //没有找到
        return -1;
    }

    public String Dijkstra(String start,String end){

        int arraymax = connect.citynum+1;

        //获取起点终点的位置
        int startindex = Locate(start);
        int endindex = Locate(end);


        //存取路径的数组
        int[][] path = new int[arraymax][arraymax];

        //判断结点是否被访问过
        boolean[] visit = new boolean[arraymax];
        for(int i=1;i<=connect.citynum;i++){ visit[i] = false; }

        //记录权值的大小
        double[] weight = new double[arraymax];
        for(int i=1;i<=connect.citynum;i++){ weight[i] = Double.MAX_VALUE; }

        Stack<Integer> stack = new Stack<>();
        weight[startindex] = 0;
        stack.push(startindex);
        while(!stack.empty()){
            double min = Double.MAX_VALUE;
            int minindex = -1;
            int current = stack.pop();
            visit[current] = true;
            for(int i=0;i<Vertexlist[current].list.size();i++){

                int j = Vertexlist[current].list.get(i).adjvex;
                double temp =  Vertexlist[current].list.get(i).weight;
                //从当前结点找能到达的最近的没被访问过的结点
                if(!visit[j] && min > temp) {
                    minindex = j;
                }

                //原来没有路径或者现在有更短的路径
                if(!visit[j] && weight[j] > weight[current] + temp){
                    weight[j] = weight[current] + temp;
                    //路径的继承
                    int t=1;
                    while(path[current][t] != 0){
                        path[j][t] = path[current][t];
                        t++;
                    }
                    path[j][t] = current;
                    path[j][t+1] = 0;
                }

                if(minindex > -1){
                    stack.push(minindex);
                }
            }
        }

        /*System.out.println("最省钱的方式：");
        for(int i=1;i<=connect.citynum;i++){
            if(i == startindex)
                continue;
            System.out.print(Vertexlist[startindex].city.name+"--->"+Vertexlist[i].city.name+":  ");
            for(int j=1;path[i][j]!=0;j++) {
                System.out.print(Vertexlist[path[i][j]].city.name + "  ");
            }
            System.out.println(Vertexlist[i].city.name+"  price:  "+weight[i]);
        }*/
        StringBuilder result = new StringBuilder();
        result.append("最省钱的方式：\n");
        for(int i=0;path[endindex][i]!=0;i++){
            result.append(Vertexlist[path[endindex][i]].city.name + "  ");
        }
        result.append(Vertexlist[endindex].city.name+"  price:  "+weight[endindex]);

        return result.toString();
    }

    //最少中转次数
    public int BFS(String start,String end){

        int arraymax = connect.citynum+1;
        //获取起点终点的位置
        int startindex = Locate(start);
        int endindex = Locate(end);

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
                if(!visit[j]){
                    visit[j] = true;
                    //已经找到该点
                    if(j == endindex){
                        return curnode.count;//能够直达就不用中转
                    }
                    node nextnode = new node();
                    nextnode.index = j;
                    nextnode.count = curnode.count+1;
                    queue.offer(nextnode);
                }
            }
        }
        //从start无法到达end
        return -1;
    }
}

class node{
    int index;
    int count;
}

class Time{

    //计算两个日期的时间差(单位为小时)
    public double timedifference(Timestamp start,Timestamp end){
        return (end.getTime()-start.getTime())*1.0/(1000*60*60);
    }

    //比较两个时间的先后
    public int timeisbefore(Timestamp a,Timestamp b){
        if(a.before(b))
            return 1;
        return 0;
    }

    //String转化为Timestamp
    public Timestamp DateToTimestamp(String datestring) throws ParseException{
        SimpleDateFormat df =new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
        java.util.Date date = df.parse(datestring);
        return new Timestamp(date.getTime());
    }
}













