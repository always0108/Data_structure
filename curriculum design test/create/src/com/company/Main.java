package com.company;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.util.LinkedList;
import java.util.Scanner;
import java.sql.*;

public class Main {

    public static void main(String[] args) {

        SimpleDateFormat df =new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
        java.util.Date date = df.parse("2018-01-03 17:00:00");
        Timestamp start = new Timestamp(date.getTime());
        date = df.parse("2018-01-03 20:30:00");
        Timestamp end = new Timestamp(date.getTime());
        

    }
}
