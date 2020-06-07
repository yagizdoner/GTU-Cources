/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg141044062;
import java.util.Iterator;
import javafx.util.Pair;

/**
 *
 * @author YAGIZ-PC
 */
public class Main {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        System.out.println("The Test of GTUSet");
        System.out.println("++++++++++++++++++++");
        GTUSet set = new GTUSet();
        System.out.printf("Is Set Array Empty : %s \n",set.empty());
        set.insert(3);
        System.out.println(set);
        System.out.println("--------------");
        set.insert(5);
        System.out.println(set);
        System.out.println("--------------");
        set.insert(7);
        System.out.println(set);
        System.out.println("Is Array Contain the element 7 ?");
        System.out.println(set.count(7));
        System.out.println("Is Array Contain the element 4 ?");
        System.out.println(set.count(4));
        System.out.println("--------------");
        set.insert(9);
        System.out.println(set);
        System.out.println("--------------");
        set.erase(5);
        System.out.println(set);
        System.out.println("--------------");
        set.erase(7);
        System.out.println(set);
        System.out.println("--------------");
        System.out.println("Set is clearing...");
        set.clear();
        System.out.println(set);
        System.out.printf("Is Array Empty : %s \n\n\n",set.empty());
        System.out.println("The Test of GTUMap");
        System.out.println("+++++++++++++++++++++");
        GTUMap map = new GTUMap();
        System.out.printf("Is Array Empty : %s \n",map.empty());
        Pair<Integer,Integer> pair1 = new Pair(2,3);
        map.insert(pair1);
        System.out.println(map);
        System.out.println("--------------");
        Pair<Integer,Integer> pair2 = new Pair(2,5);
        map.insert(pair2);
        System.out.println(map);
        System.out.println("--------------");
        Pair<Integer,Integer> pair3 = new Pair(7,3);
        map.insert(pair3);
        System.out.println(map);
        System.out.println("--------------");
        Pair<Integer,Integer> pair4 = new Pair(6,3);
        map.insert(pair4);
        System.out.println(map);
        System.out.println("--------------");
        map.erase(pair4);
        System.out.println(map);
        System.out.println("--------------");
        map.erase(pair3);
        System.out.println(map);
        System.out.println("--------------");
        System.out.println("Map is clearing...");
        map.clear();
        System.out.println(map);
        System.out.println("--------------");
        System.out.printf("Is Array Empty : %s \n",map.empty());   
    }
}
