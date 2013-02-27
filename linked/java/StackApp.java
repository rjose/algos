class MemNode {
        int value;
        MemNode link;
        MemManager memManager;

        public MemNode() {
                link = null;
                value = 0;
        }

        public void setLink(MemNode next) {
                link = next;
        }

        public void setValue(int val) {
                value = val;
        }

        public int getValue() {
                return value;
        }

        public MemNode nextNode() {
                return link;
        }

        public void setMemManager(MemManager mgr) {
                memManager = mgr;
        }

        public void free() throws Exception {
                if (memManager == null) {
                        throw new Exception("Ouch");
                }
                memManager.free(this);
        }
}

class MemManager {
        public static int NUM_NODES = 100;
        public static MemNode[] nodes = new MemNode[NUM_NODES];
        public MemNode available;

        public MemManager() {
                // Create nodes
                for (int i=0; i < NUM_NODES; i++) {
                        nodes[i] = new MemNode();
                }

                // Hook up nodes
                for (int i=0; i < NUM_NODES-1; i++) {
                        nodes[i].setLink(nodes[i+1]);
                }
                available = nodes[0];
        }

        public MemNode allocateNode() {
                MemNode result = available;
                available = result.nextNode();
                result.setMemManager(this);
                return result;
        }

        public void free(MemNode node) {
                node.setLink(available);
                available = node;
        }
}

class Stack {
        MemManager memManager;
        MemNode top;

        public Stack(MemManager mgr) {
                memManager = mgr;
                top = null;
        }

        public void push(int val) {
                MemNode node = memManager.allocateNode();
                node.setValue(val);
                node.setLink(top);
                top = node;
        }

        public int pop() throws Exception {
                if (top == null)
                        throw new Exception("Underflow");
                int result = top.getValue();
                MemNode p = top;
                top = p.nextNode();
                p.free();
                return result;
        }
}

public class StackApp {

        public static void main(String[] args) {
                System.out.println("Howdy, Java!");
                MemManager memmgr = new MemManager();
                Stack stack = new Stack(memmgr);
                stack.push(111);
                stack.push(222);
                try {
                        int value = stack.pop();
                }
                catch (Exception e) {
                        System.out.println("pop");
                }
        }
}
