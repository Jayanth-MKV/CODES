package MultiThreading;

public class Producer_consumer_problem {
    public static void main(String[] args) {
        Producer producer = new Producer();
        Thread threadp=new Thread(producer);
        threadp.start();

        Thread threadc=new Thread(new Consumer(producer));
        threadc.start();
    }
}
