import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;

public class Main {
    static class Pii implements Comparable {
        int first;
        int second;

        public Pii() {
            first=0;
            second=0;
        }
        public Pii(int first, int second) {
            this.first = first;
            this.second = second;
        }

        public int compareTo(Object o) {
            Pii p = (Pii) o;
            return first - ((Pii) o).first;
        }
        public String toString() {
            return first + " " + second;
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String[] input = br.readLine().split(" ");
        int N = Integer.parseInt(input[0]);
        int M = Integer.parseInt(input[1]);
        int K = Integer.parseInt(br.readLine());

        List<List<Pii>> edge = new ArrayList<>();
        for (int i = 0; i <= N; i++) {
            edge.add(new ArrayList<>());
        }
        for (int i = 0; i < M; i++) {
            String[] edges = br.readLine().split(" ");
            int u = Integer.parseInt(edges[0]);
            int v = Integer.parseInt(edges[1]);
            int w = Integer.parseInt(edges[2]);
            edge.get(u).add(new Pii(v, w));
        }
        int maxValue = (int)1e9;
        PriorityQueue<Pii> pq = new PriorityQueue<>();
        List<Integer> dp = new ArrayList<>(Collections.nCopies(N+1, maxValue));
        dp.set(K, 0);

        pq.add(new Pii(dp.get(K), K));
        while (!pq.isEmpty()) {
            Pii poll = pq.poll();
            int distance = poll.first;
            int cur = poll.second;

            if (dp.get(cur) != distance) {
                continue;
            }
            for (Pii d : edge.get(cur)) {
                int next = d.first;
                int nextDistance = distance + d.second;
                if (nextDistance < dp.get(next)) {
                    dp.set(next, nextDistance);
                    pq.add(new Pii(nextDistance, next));
                }
            }
        }
        for (int i = 1; i <= N; i++) {
            System.out.println(dp.get(i)==maxValue ? "INF" : dp.get(i));
        }
    }
}
