# Algoritmo para o acionamento do paraquedas
O código foi escrito em Arduino e contêm os seguintes métodos:

```cpp
void build_queue();
```

- Monta a _queue_ com os 100 primeiros valores lidos pelo sensor

```cpp
void update_queue(double last_alt_value);
```

- Atualiza a _queue_

```cpp
void print_queue();
```

- Imprime os valores da _queue_

```cpp
bool free_fall();
```

- Retorna se o foguete está em queda livre

