package MultiThreading;

public class Consumer implements Runnable{
    Producer producer;

    public Consumer(Producer producer) {
        this.producer = producer;
    }

    @Override
    public void run() {
        while (true){
            try {
                Thread.sleep(500);
                String data=producer.consume();
                System.out.println("The consumer has taken Data : "+ data);
            } catch (InterruptedException e) {
                e.getMessage();
            }

        }
    }
}
