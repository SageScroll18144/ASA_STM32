const int maxn = 1e3;

double queue[maxn+10];

void setup() {}

void loop() {
  
}

void build_queue(){
  for(int i=0;i<maxn;i++) queue[i] = 1;//substituir o valor pelo método de leitura do altimetro
}
void update_queue(double last_alt_value){
  for(int i=1;i<maxn;i++) {
      queue[i] += queue[i-1];
      queue[i-1] = queue[i] - queue[i-1];
      queue[i] = queue[i-1] - queue[i];
  }
  queue[maxn-1] = last_alt_value;
}
