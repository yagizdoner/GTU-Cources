/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pkg141044062;
import java.util.Iterator;

public class GTUSet<T> implements GTUSetInt<T> {
    private final int maxSize = 1000; // maximum size of array. Selected randomly.
    protected T[] arr;
  
    @Override
    public String toString(){
        int i=0;
        if(this.size() == 0){ // eleman yoksa;
            return String.format("There is not element.");
        }
        for(T temp : arr){
            System.out.printf("Index of %d is %s.\n",i,arr[i]);
            ++i;
        }
        return String.format("Size of the Array is %d", this.size());
    }
    
    @Override
    public boolean empty() {
        return arr == null;
    }

    @Override
    public int size() {
        if(this.empty())
            return 0;
        return arr.length;
    }

    @Override
    public int max_size() {
        return maxSize;
    }

    @Override
    public void insert(T value){
        try{
            int arrSize = this.size(); // eski size tutulur.
            if(arrSize == 0){ // ilk kez atanıyorsa atama yapılır.
                arr = (T[]) new Object[1];
                arr[0] = value;
            }
            else{ // 2. veya sonraki doldurmalarda bu blok çalışır.
                if(this.count(value)){   // elemanı sette bulursa exception fırlatır.
                    throw new IllegalArgumentException();
                }
                T[] temp = (T[]) new Object[arrSize];
                int i=0;
                for(T cont : arr){ // arr imi bir temporary de tuttum.
                    temp[i] = arr[i];
                    ++i;
                }
                arr = (T[]) new Object[arrSize+1]; // yeni arr i kurdum
                int k=0;
                for(T cont : temp){  // temporary mi yeni arr ime atadım.
                    arr[k] = temp[k];
                    ++k;
                }
                arr[k] = value; // eklenmesini istediği değeri atadım.
            }
        }
        catch(IllegalArgumentException exc){
            System.err.println("Given Value is Already in Set.");
        }
    }
    
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){
        return null;
    /*    int appendSize=0;
        for(int i=0; i<other.size() ;++i){
            if( ! this.count(other[i])){ // other ın elemanı bizim arr imizde yoksa.
                ++appendSize;
            }
        }*/
    }

    @Override
    public void erase(T value) {
        int arrSize = this.size(); // eski size tutulur.
        int i,k;
        if(arrSize == 1){ // tek kalan eleman siliniyorsa;
            arr = null; // array null ile kapatılır.
        }
        else{ // arrayimde birden fazla eleman varsa birer birer silmek için bu blok çalışacak.
            T[] temp = (T[]) new Object[arrSize-1];
            for(i=0,k=0; i<arrSize; ++i){
                if(arr[i] != value){
                    temp[k] = arr[i];
                    k++;
                }
            }
            arr = (T[]) new Object[arrSize-1]; // yeni arr i kurdum
            k=0;
            for(T cont : temp){  // temporary mi yeni arr ime atadım.
                    arr[k] = temp[k];
                    ++k;
            }
        }
    }

    @Override
    public void clear() {
        arr = null;
    }

    @Override
    public Iterator<T> find(T value) {
        Iterator<T> res;
        int i;
        for(i=0; i<arr.length; ++i){
            if(arr[i] == value)
                break;
        }
        res = (Iterator) arr[i];
        return res;
    }
    
    @Override
    public boolean count(T value) {
        int i;
        for(i=0; i<arr.length; ++i){
            if(arr[i] == value){
                return true; // if found, return.
            }
        }
        return false; // if not found;
    }

    @Override
    public Iterator<T> begin() {
        Iterator<T> res = (Iterator<T>) arr[0];
        return res;
    }

    @Override
    public Iterator<T> end() {
        Iterator<T> res = (Iterator) arr[arr.length-1];
        return res;
    }
    
    public class GTUIterator {
        public T next(){
            return arr[0];      
        }
        
        public T previous(){
            return arr[0];
        }
        
        public boolean hasNext(){
            return this.next() != null;
        }
        
        public boolean hasPrevious(){
            return this.previous() != null;
        }
    }
}
