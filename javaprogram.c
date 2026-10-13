class SharedBuffer {
    private int value;
    private boolean available = false;

    // Producer produces a value
    synchronized void produce(int value) {
        try {
            while (available) {
                wait();
            }

            this.value = value;
            System.out.println("Producer produced: " + value);

            available = true;
            notify();

        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }

    // Consumer consumes the value
    synchronized void consume() {
        try {
            while (!available) {
                wait();
            }

            System.out.println("Consumer consumed: " + value);

            available = false;
            notify();

        } catch (InterruptedException e) {
            System.out.println(e);
        }
    }
}

// Producer thread
class Producer extends Thread {
    SharedBuffer buffer;

    Producer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        for (int i = 1; i <= 10; i++) {
            buffer.produce(i);
        }
    }
}

// Consumer thread
class Consumer extends Thread {
    SharedBuffer buffer;

    Consumer(SharedBuffer buffer) {
        this.buffer = buffer;
    }

    public void run() {
        for (int i = 1; i <= 10; i++) {
            buffer.consume();
        }
    }
}

// Main class
public class ProducerConsumer {
    public static void main(String[] args) {

        SharedBuffer buffer = new SharedBuffer();

        Producer producer = new Producer(buffer);
        Consumer consumer = new Consumer(buffer);

        producer.start();
        consumer.start();
    }
}
