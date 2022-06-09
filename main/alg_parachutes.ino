void build_queue(){
  for(int i=0;i<lim;i++) queue_weights[i] = event.orientation.y;//substituir o valor pela orientação do altimetro
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
