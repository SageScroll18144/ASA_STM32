const int parachute = 13;//mudar valor de acordo com a placa

const int maxn = 110;
const int lim = 100;

double queue_weights[maxn];

void setup() {
  Serial.begin(115200);
  build_queue();
  pinMode(parachute, OUTPUT);
}
void loop() {
  update_queue(1);
  if(free_fall()) digitalWrite(parachute, !digitalRead(parachute));
  print_queue();
  delay(10);
}

void build_queue(){
  for(int i=0;i<lim;i++) queue_weights[i] = lim-i;//substituir o valor pelo método de leitura do altimetro
}
void update_queue(double last_alt_value){
  for(int i=1;i<lim;i++) {
      queue_weights[i] += queue_weights[i-1];
      queue_weights[i-1] = queue_weights[i] - queue_weights[i-1];
      queue_weights[i] = queue_weights[i-1] - queue_weights[i];
  }
  queue_weights[lim-1] = last_alt_value;
}
void print_queue(){
  for(int i=0;i<lim;i++) {Serial.print(queue_weights[i]); Serial.print(" ");}
  Serial.println();
}
bool free_fall(){
  for(int i=lim-1;i>=3;i--){
    if(queue_weights[i]<queue_weights[i-1]&&queue_weights[i-1]<queue_weights[i-2]&&queue_weights[i-2]<queue_weights[i-3]) return true;
  }
  return false;
}
