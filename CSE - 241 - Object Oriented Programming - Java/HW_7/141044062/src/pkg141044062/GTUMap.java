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
 * @param <K>
 * @param <V>
 */
public class GTUMap<K,V> extends GTUSet<javafx.util.Pair<K,V> > {
    public V at(K k){
        int i;
        for(i=0; i<this.size(); ++i){
            if( arr[i].getKey() == k){
                return arr[i].getValue(); // if found, return.
            }
        }
        return null; // if not found;
    }
}