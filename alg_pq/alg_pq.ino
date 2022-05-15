#define ll long long int
typedef struct pair{
  double first_v;
  int second_v;  
}ii;

const int parachute = 13;//mudar valor de acordo com a placa

const int maxn = 1e3+10;
const int lim = 110;
const int lim_inv = 5000;//valor depende da 'var' lim

double queue_weights[maxn];
int tree[maxn];

void setup() {
  build_queue();
  pinMode(parachute, OUTPUT);
}

void loop() {
  update_queue(1);//substituir o valor pelo método de leitura do altimetro
  if(how_many_inv() >= lim_inv) digitalWrite(parachute, HIGH);
}

void build_queue(){
  for(int i=0;i<lim;i++) queue_weights[i] = 1;//substituir o valor pelo método de leitura do altimetro
}
void update_queue(double last_alt_value){
  for(int i=1;i<lim;i++) {
      queue_weights[i] += queue_weights[i-1];
      queue_weights[i-1] = queue_weights[i] - queue_weights[i-1];
      queue_weights[i] = queue_weights[i-1] - queue_weights[i];
  }
  queue_weights[lim-1] = last_alt_value;
}
int query_bit(int x){
    int ans = 0;
    while(x > 0){
        ans+=tree[x];
        x-=(x&-x);
    }
    return ans;
}
void update_bit(int x, int val){
    while(x < lim){
        tree[x]+=val;
        x+=(x&-x);
    }
}
ll how_many_inv(){
  ii g[maxn];
  for(int i=0;i<lim;i++){
    ii v;
    v.first_v = queue_weights[i];
    v.second_v = i+1;
    
    g[i] = v;
  }
  qsort(g, sizeof(g)/sizeof(ii), sizeof(ii), comparator);
  ll cnt = 0;

  for(int i=lim-1; i>=0;i--){
    cnt+=query_bit(g[i].second_v);
    update_bit(g[i].second_v, 1);
  }

  return cnt;
}
int comparator(const void *a, const void *b) {
   return (((ii *)a)->first_v > ((ii *)b)->first_v ? 1 : (((ii *)a)->first_v < ((ii *)b)->first_v ? -1 : 0));
}
