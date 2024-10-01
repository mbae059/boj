import java.io.*;
import java.util.*;


class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        String str = br.readLine();
        String[] s = str.split(" ");
        int N = Integer.parseInt(s[0]);
        int M = Integer.parseInt(s[1]);

        int[] arr = new int[N];
        for(int i = 0; i < N; i++) {
            int x = Integer.parseInt(br.readLine());
            arr[i] = x;
        }
        Arrays.sort(arr);
        int l = 0;
        int r = 0;
        int answer = (int)2e9;
        while(l<=r && r<N) {
            if(arr[r]-arr[l]>=M) answer = Math.min(answer, arr[r]-arr[l]);
            if(arr[r]-arr[l]<M) r++;
            else l++;
        }
        print(answer);
    }

    public static void print(int... ints) {
        for (int anInt : ints) {
            System.out.print(anInt + " ");
        }
        System.out.println();
    }
    public static void print(String... str) {
        for (String s : str) {
            System.out.print(s + " ");
        }
        System.out.println();
    }
}