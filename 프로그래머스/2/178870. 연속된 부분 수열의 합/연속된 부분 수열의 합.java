class Solution {
    class Pii {
        int a;
        int b;
        
        Pii() {
            a=b=0;
        }
        
        Pii(int a, int b) {
            this.a =a;
            this.b = b;
        }
        void renew(Pii p) {
            if((b-a ==p.b-p.a && a>p.a) || (b-a>p.b-p.a)) {
                a = p.a;
                b = p.b;
            }
        }
    }
    int N;
    Pii p = new Pii(1_000_000, 3_000_000);
    public int[] solution(int[] sequence, int k) {
        N = sequence.length;
        int[] arr = new int[N+1];
        int[] prefix = new int[N+1];
        for(int i=0;i<N;i++) {
            arr[i+1] = sequence[i];
            prefix[i+1] = prefix[i] + arr[i+1];
        }
        for(int i=1;i<=N;i++) {
            int l = i;
            int r = N;
            
            int idx = i;
            while(l<=r) {
                int mid = (l+r)>>1;
                int val = prefix[mid] - prefix[i-1];
                if(val>k) r = mid-1;
                else if(val<k) l = mid+1;
                else {
                    idx = mid;
                    break;
                }
            }
            if(prefix[idx]-prefix[i-1]==k) {
                p.renew(new Pii(i, idx));
            }
        }
        
        
        
        int[] answer = {p.a-1, p.b-1};
        return answer;
    }
}