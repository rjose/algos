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
}

public class StackApp {

        public static void main(String[] args) {
                System.out.println("Howdy, Java!");
                MemManager memmgr = new MemManager();
                MemNode n1 = memmgr.allocateNode();
                MemNode n2 = memmgr.allocateNode();

                try {
                        n1.free();
                }
                catch (Exception e) {
                        System.out.println("Unable to free");
                }
        }
}
