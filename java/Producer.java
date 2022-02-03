package MultiThreading;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

public class Producer implements Runnable{

    private static final int MAX_SIZE = 4;
    private final List<String> list = new ArrayList<>();

    @Override
    public void run() {
        try {
            while(true){
                Thread.sleep(300);
                produce();

            }
        }catch (Exception e){
            System.out.println(e.getMessage());
        }
    }

    private synchronized void produce() throws InterruptedException {

        while(list.size()==MAX_SIZE){
            wait();
        }
        String data= LocalDateTime.now().toString();
        list.add(data);
        System.out.println("The Producer added data");
        System.out.println("The Queue contains : "+list.size()+" items");
        notify();
    }

    public synchronized String consume() throws InterruptedException {
        notify();
        while (list.isEmpty()){
            wait();
        }
        String data = list.get(0);;
        list.remove(data);
        System.out.println("The Queue contains : "+list.size()+" items");
        return data;
    }
}
