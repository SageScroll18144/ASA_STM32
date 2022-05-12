const int maxn = 1e3+10;

double queue[maxn];

void setup() {}

void loop() {
  
}

void build_queue(){
  for(int i=0;i<maxn;i++) queue[i] = 1;//substituir o valor pelo método de leitura do altimetro
}
void update_queue(int last_alt_value){
  for(int i=1;i<maxn;i++) {
      vet[i] += vet[i-1];
      vet[i-1] = vet[i] - vet[i-1];
      vet[i] = vet[i-1] - vet[i];
  }
  vet[maxn-1] = last_alt_value;
}
