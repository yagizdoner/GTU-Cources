/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg141044062;
import java.util.Iterator;

/**
 *
 * @author YAGIZ-PC
 * @param <T>
 */
public interface GTUSetInt<T> {
    boolean empty(); 
    int size();      
    int max_size(); 
    void insert(T value); 
    GTUSetInt<T> intersection(GTUSetInt<T> other);
    void erase(T value); 
    void clear(); 
    Iterator<T> find(T value);
    boolean count(T value);  
    Iterator<T> begin();
    Iterator<T> end();
}
