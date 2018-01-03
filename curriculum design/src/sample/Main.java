package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import java.sql.*;
import java.sql.Driver;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.DateTimeException;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;


public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception{
        Scanner input = new Scanner(System.in);
        ConnectDatebase connect = new ConnectDatebase();
        Graph graph = new Graph(connect);
        graph.Create();

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
        route.time_consuming = 4;
        //connect.Add_Route(route);*/

        /*City city = new City();
        city.name = "哈尔滨";
        city.brief = "东北区域中心城市";
        connect.Add_City(city);*/
        connect.close();

        /*Parent root = FXMLLoader.load(getClass().getResource("login.fxml"));
        primaryStage.setTitle("NTCS");
        primaryStage.setScene(new Scene(root, 800, 400));
        primaryStage.show();*/
    }

    public static void main(String[] args) {
        launch(args);
    }
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
    public boolean Add_Route(Timetable route) throws SQLException{
        try{
            stmt = conn.prepareStatement(
               "INSERT INTO Timetable(start,end,distance,vehicle,vehicle_number,depart_time,arrive_time,time_consuming,price)" +
                       "VALUES (?,?,?,?,?,?,?,?,?)");
            stmt.setString(1,route.start);
            stmt.setString(2,route.end);
            stmt.setDouble(3,route.distance);
            stmt.setString(4,route.vehicle);
            stmt.setString(5,route.vehicle_number);
            stmt.setTimestamp(6,route.depart_time);
            stmt.setTimestamp(7,route.arrive_time);
            stmt.setDouble(8,route.time_consuming);
            stmt.setDouble(9,route.price);
            stmt.execute();
            return true;
        }catch (SQLException e){
            e.printStackTrace();
            return false;
        }
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




}



class User{
    int id;              //长度
    String name;         //20
    String password;     //20
    String type;         //10
    String question;     //50
    String answer;       //20

    User(){}
}

class City{
    int id;               //长度
    String name;          //30
    String brief;         //255

    City(){}
}

class Timetable{
    int id;               //长度
    String start;         //30
    String end;           //30
    double distance;
    String vehicle;       //20
    String vehicle_number;//20
    Timestamp depart_time;
    Timestamp arrive_time;
    double time_consuming;
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

    Graph(){}

    Graph(ConnectDatebase connect){
        this.connect = connect;
    }

    public VertexNode[] Create ()
            throws java.sql.SQLException {

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
            int x = Locate(start, Vertexlist);
            int y = Locate(end, Vertexlist);
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
        //Dijkstra(Vertexlist,"西安","北京");
        System.out.print("最少中转次数： ");
        System.out.println(BFS(Vertexlist,"西安","哈尔滨"));
        return Vertexlist;
    }

    public int Locate(String name, VertexNode[] Vertexlist) {
        for (int i = 1; i <= connect.citynum; i++) {
            //查找到对应的位置
            if (name.equals(Vertexlist[i].city.name))
                return i;
        }
        //没有找到
        return -1;
    }

    void Dijkstra(VertexNode[] Vertexlist,String start,String end){

        int arraymax = connect.citynum+1;

        //获取起点终点的位置
        int startindex = Locate(start, Vertexlist);
        int endindex = Locate(end, Vertexlist);


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

        System.out.println("最省钱的方式：");
        for(int i=1;i<=connect.citynum;i++){
            if(i == startindex)
                continue;
            System.out.print(Vertexlist[startindex].city.name+"--->"+Vertexlist[i].city.name+":  ");
            for(int j=1;path[i][j]!=0;j++) {
                System.out.print(Vertexlist[path[i][j]].city.name + "  ");
            }
            System.out.println(Vertexlist[i].city.name+"  price:  "+weight[i]);
        }
    }

    //最少中转次数
    public int BFS(VertexNode[] Vertexlist,String start,String end){

        int arraymax = connect.citynum+1;
        //获取起点终点的位置
        int startindex = Locate(start, Vertexlist);
        int endindex = Locate(end, Vertexlist);

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













