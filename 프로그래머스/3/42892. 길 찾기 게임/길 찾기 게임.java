import java.util.*;

class Solution {
    int[][] answer;
    int N;    
    int idx= 0;
    class Node {
        int x;
        int y;
        int value;
        Node left;
        Node right;
        
        public Node(int x, int y, int value, Node left, Node right) {
            this.x=x;
            this.y=y;
            this.value=value;
            this.left=left;
            this.right=right;
        }
    }
        
    public void print(int... args) {
        for(int i : args) {
            System.out.print(i + " ");
        }
        System.out.println();
    }
    public void print(Node node) {
        print(node.x, node.y);
    }
    public int[][] solution(int[][] nodeinfo) {
        N = nodeinfo.length;
        answer = new int[2][N];
        Node[] node = new Node[N];
        for(int i=0;i<N;i++) {
            node[i] = new Node(nodeinfo[i][0], nodeinfo[i][1], i+1, null, null);
        }
        
        Arrays.sort(node, new Comparator<Node>() {
            public int compare(Node n1, Node n2) {
                if(n1.y==n2.y) return n1.x-n2.x;
                return n2.y-n1.y;
            }
        });
        
        for(int i=1;i<N;i++) {
            insertNode(node[0], node[i]);
        }
        idx = 0;
        preOrder(node[0]);
        idx = 0;
        postOrder(node[0]);
        return answer;
    }
    
    void insertNode(Node parent, Node child) {
        if(parent.x>child.x) {
            if(parent.left==null) parent.left = child;
            else insertNode(parent.left, child);
        }
        else {
            if(parent.right==null) parent.right = child;
            else insertNode(parent.right, child);
        }
    }
    
    void preOrder(Node node) {
        if(node!=null) {
            answer[0][idx++] = node.value;
            preOrder(node.left);
            preOrder(node.right);
        }
    }
    
    void postOrder(Node node) {
        if(node!=null) {
            postOrder(node.left);
            postOrder(node.right);
            answer[1][idx++] = node.value;
        }
    }
}