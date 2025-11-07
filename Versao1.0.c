#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
// adicionar func de ordenar o cardápio
// adiconar func de item no cardápio
// adicionar func de remover item do cardápio
// adicionar func de alterar item do cardápio (inflação)
//qr code TALVEZ
#define MAX_ITEMS 11
#define MAX_NAME_LENGTH 100
#define MAX_ADDRESS_LENGTH 120
#define MAX_QUEUE_SIZE 100
#define ANSI_COLOR_GREEN "\x1b[32m" //verde
#define ANSI_COLOR_RED "\x1b[31m" //vermelho
#define ANSI_COLOR_RESET "\x1b[0m" //default
typedef struct {
char *name;
float price;
} MenuItem;
typedef struct {
char item_name[MAX_NAME_LENGTH];
int quantity;
} OrderItem;
typedef struct {
char *bairro;
char *cidade;
char *rua;
char *numero_casa;
char *complemento;
} Address;
typedef struct {
char *customer_name;
Address *address;
OrderItem *items;
float total_price;
int num_items;
time_t payment_time; // USAR NO FUTURO
} Order;
//funcs de tratamento
bool is_Name_Valid(char *customer_name){
int name_length = strlen(customer_name);
for(int i = 0; i < name_length;i++){
if(isalpha(customer_name[i])){
return true;
}
}
return false;
}
bool is_Bairro_Valid(char * bairro){
int bairro_length = strlen(bairro);
for(int i = 0; i < bairro_length;i++){
if(isalpha(bairro[i])){
return true;
}
}
return false;
}
bool is_Cidade_Valid(char *cidade){ //ALTERAR ESSA FUNC PAREA QUE APENAS
AS SIGLAS DOS ESTADOS SEJAM ACEITAS POR EXEMPLO "SP" E TAMBÉM TALVEZ
LIMITAR OS ESTADOS
int cidade_length = strlen(cidade);
for(int i = 0; i < cidade_length;i++){
if(isalpha(cidade[i])){
return true;
}
}
return false;
}
bool is_Rua_Valid(char *rua){
int rua_length = strlen(rua);
for(int i = 0; i < rua_length;i++){
if(isalpha(rua[i])){
return true;
}
}
return false;
}
bool is_House_Number_Valid(char *house_number){
int house_number_length = strlen(house_number);
for(int i = 0; i < house_number_length;i++){
if(isalpha(house_number[i])){
return false;
}
}
return true;
}
bool is_Selected_Item_Valid(int selected_item, int menu_size){
if(selected_item < 0 || selected_item >=menu_size){
return false;
}
return true;
}
bool is_Selected_Order_Valid(int selected_order_number, int waiting_queue_size){
if(selected_order_number < 0 || selected_order_number >= waiting_queue_size){
return false;
}
return true;
}
bool is_Selected_Quantity_Valid(int quantity){
if(quantity <= 0){
return false;
}
return true;
}
bool is_End_Order_Input_Valid(char option){
if(option == 's' || option == 'n'){
return true;
}
return false;
}
bool is_Card_Valid(){
// checar se o cartão é válido
return true;
}
bool handle_Credit_Card_Payment(){
return true;
}
bool handle_Debit_Card_Payment(){
return true;
}
bool handle_Pix_Payment(){
return true;
}
void clear(void) {
while (getchar() != '\n'); // limpa o input
}
//////
void add_items_to_order(Order *order, char *item_name, int quantity){ //func que
adiciona os items e sua quantidade ao pedido
if(order->items == NULL){ //caso seja o primeiro item
order->items = (OrderItem *)malloc(sizeof(OrderItem));
} else {
order->items = (OrderItem *)realloc(order->items,(order-
>num_items+1)*sizeof(OrderItem)); //caso seja o segundo ou mais
}
strcpy(order->items[order->num_items].item_name, item_name); //adiciona o
nome do item
order->items[order->num_items].quantity = quantity; // adiciona a quantidade
order->num_items++; // aumanta o número de items em 1
}
void add_order_to_queue(Order *waiting_queue, Order new_order, int
*waiting_queue_size) {
if (*waiting_queue_size < MAX_QUEUE_SIZE) {
waiting_queue[*waiting_queue_size] = new_order;
(*waiting_queue_size)++;
printf(ANSI_COLOR_GREEN "\nPedido adicionado à fila de espera.\n"
ANSI_COLOR_RESET);
} else {
printf(ANSI_COLOR_RED "\nA fila de espera está cheia. Não é possível
adicionar mais pedidos.\n" ANSI_COLOR_RESET);
}
}
bool payment(float total_price) {
int payment_choice;
printf("\nValor total do pedido: R$%.2f\n",total_price);
do {
printf("\n-----Forma de Pagamento------\n");
printf("1. Crédito\n");
printf("2. Débito\n");
printf("3. Pix\n");
printf("\nEscolha uma opção de pagamento: ");
scanf("%d", &payment_choice);
switch (payment_choice) {
case 1:
printf("Você escolheu pagar com cartão de crédito.\n");
return handle_Credit_Card_Payment();
case 2:
printf("Você escolheu pagar com cartão de débito.\n");
return handle_Debit_Card_Payment();
case 3:
printf("Você escolheu pagar com Pix.\n");
return handle_Pix_Payment();
default:
printf("Opção de pagamento inválida. Por favor, escolha novamente.\n");
}
} while (payment_choice < 1 || payment_choice > 3);
return false;
}
void make_order(Order *waiting_queue, MenuItem *menu, int menu_size, int
*waiting_queue_size) { // TALVEZ DEVERIAMOS LIMITAR A CIDADE EM QUE A
ENTREGA PODE SER FEITA
printf("\n------Fazer Pedido------\n");
char customer_name[MAX_NAME_LENGTH];
char cidade[MAX_ADDRESS_LENGTH];
char bairro[MAX_ADDRESS_LENGTH];
char rua[MAX_ADDRESS_LENGTH];
char numero_casa[MAX_ADDRESS_LENGTH];
char complemento[MAX_ADDRESS_LENGTH];
char end_order;
float total_price = 0.0;
clear();
printf("\nNome do cliente: ");
scanf("%[^\n]", customer_name);
while (!is_Name_Valid(customer_name)) {
clear();
printf(ANSI_COLOR_RED "O nome deve conter apenas letras\n"
ANSI_COLOR_RESET);
printf("\nNome do cliente: ");
scanf("%[^\n]", customer_name);
}
clear();
printf("Cidade: ");
scanf("%[^\n]", cidade);
while (!is_Cidade_Valid(cidade)) {
clear();
printf(ANSI_COLOR_RED "\nA cidade deve conter apenas letras\n"
ANSI_COLOR_RESET);
printf("Cidade: ");
scanf("%[^\n]", cidade);
}
clear();
printf("Bairro: ");
scanf("%[^\n]", bairro);
while (!is_Bairro_Valid(bairro)) {
clear();
printf(ANSI_COLOR_RED "\nO bairro deve conter apenas letras\n"
ANSI_COLOR_RESET);
printf("Bairro: ");
scanf("%[^\n]", bairro);
}
clear();
printf("Rua: ");
scanf("%[^\n]", rua);
while(!is_Rua_Valid(rua)){
clear();
printf(ANSI_COLOR_RED "\n A rua deve conter apenas letras\n"
ANSI_COLOR_RESET);
printf("Rua: ");
scanf("%[^\n]", rua);
}
clear();
printf("Número da casa: ");
scanf("%[^\n]", numero_casa);
while (!is_House_Number_Valid(numero_casa)) {
clear();
printf(ANSI_COLOR_RED "\n Apenas números são aceitos para essa opção\n"
ANSI_COLOR_RESET);
printf("Número da casa: ");
scanf("%[^\n]", numero_casa);
clear();
}
clear();
printf("Complemento (opcional): ");
fgets(complemento, sizeof(complemento), stdin);
if (complemento[strlen(complemento) - 1] == '\n') {
complemento[strlen(complemento) - 1] = '\0';
}
if (strlen(complemento) == 0) {
complemento[0] = ' ';
complemento[1] = '\0';
}
Address *address = malloc(sizeof(Address));
address->cidade = strdup(cidade);
address->bairro = strdup(bairro);
address->numero_casa = strdup(numero_casa);
address->complemento = strdup(complemento);
Order new_order;
new_order.customer_name = strdup(customer_name);
new_order.items = NULL;
new_order.num_items = 0;
new_order.address = address;
do {
end_order = 'n';
int selected_item;
int quantity;
printf("\nSelecione um item do cardápio: \n");
for (int i = 0; i < menu_size; i++) {
printf("%d. %s - R$%.2f\n", i + 1, menu[i].name,menu[i].price);
}
printf("\nNúmero do item: ");
scanf("%d", &selected_item);
selected_item--;
while (!is_Selected_Item_Valid(selected_item, menu_size)) {
printf(ANSI_COLOR_RED "O item selecionado é inválido"
ANSI_COLOR_RESET);
scanf("%d", &selected_item);
selected_item--;
}
printf("Quantidade desejada: ");
scanf("%d", &quantity);
while (!is_Selected_Quantity_Valid(quantity)) {
printf(ANSI_COLOR_RED "A quantdade deve ser maior que zero"
ANSI_COLOR_RESET);
scanf("%d", &quantity);
}
float item_price = menu[selected_item].price;
total_price += item_price * quantity;
new_order.total_price = total_price;
add_items_to_order(&new_order, menu[selected_item].name, quantity);
printf("Deseja encerrar o pedido? (s/n): ");
scanf(" %c", &end_order);
while (!is_End_Order_Input_Valid(end_order)) {
printf(ANSI_COLOR_RED "Apenas s ou n" ANSI_COLOR_RESET);
printf("\nDeseja encerrar o pedido? (s/n): ");
scanf(" %c", &end_order);
}
} while (tolower(end_order) == 'n');
if(payment(total_price)){
//new_order.payment_time = time(NULL); NÃO FUNCIONA AINDA
add_order_to_queue(waiting_queue, new_order, waiting_queue_size);
}
}
void move_order_to_ready_stack(Order *waiting_queue, Order *ready_stack, int
waiting_queue_size, int *ready_stack_top){ //O PEDIDO QUE FOI MOVIDO
PRECISA SAIR DA LISTA DE ESPERA, ISSO NÃO ACONTECE (BUG)
printf("\n------Adicionar pedido pronto------\n");
if(waiting_queue_size > 0){
printf("Pedidos na Fila de espera:\n ");
for(int i = 0; i < waiting_queue_size;i++){
printf("Número do pedido: %d",i+1);
printf("\nCliente: %s\n", waiting_queue[i].customer_name);
printf("\nEndereço: %s %s %s %s %s\n",waiting_queue[i].address-
>cidade,waiting_queue[i].address->bairro,waiting_queue[i].address-
>rua,waiting_queue[i].address->numero_casa,waiting_queue[i].address-
>complemento);
printf("\nItens do Pedido:\n");
for (int j = 0; j < waiting_queue[i].num_items; j++) {
printf("- %d x %s\n", waiting_queue[i].items[j].quantity,
waiting_queue[i].items[j].item_name);
}
}
printf("----------------------------\n");
} else if(waiting_queue_size <= 0){
printf(ANSI_COLOR_GREEN "Não há pedidos na fila de espera"
ANSI_COLOR_RESET);
}
int select_order_number;
printf("\nSelecione o número do pedido que será movido: ");
scanf("%d",&select_order_number);
select_order_number--;
while(!is_Selected_Order_Valid(select_order_number, waiting_queue_size)){
printf(ANSI_COLOR_RED "\nNúmero inválido\n" ANSI_COLOR_RESET);
scanf("%d",&select_order_number);
select_order_number--;
}
Order ready_order = waiting_queue[select_order_number];
ready_stack[++(*ready_stack_top)] = ready_order;
for (int i = select_order_number; i < waiting_queue_size - 1; i++) {
waiting_queue[i] = waiting_queue[i + 1];
} //bloco que preenche os espaços vazios da fila
waiting_queue_size--;
printf(ANSI_COLOR_GREEN "Pedido pronto!\n" ANSI_COLOR_RESET );
}
void show_first_waiting_order(Order *waiting_queue, int waiting_queue_size,
MenuItem *menu, int menu_size) {
printf("\n------Próximo Pedido na Fila------\n");
if (waiting_queue_size > 0) {
Order first_order = waiting_queue[0];
printf("\nNúmero do pedido: 1");
printf("\nCliente: %s\n", first_order.customer_name);
printf("\n------Endereço------\n");
printf("\nCidade: %s\n", first_order.address->cidade);
printf("\nBairro: %s\n", first_order.address->bairro);
printf("\nNúmero da casa: %s\n", first_order.address->numero_casa);
printf("\nComplemento: %s\n", first_order.address->complemento);
printf("------------");
printf("\nTotal: R$%.2f\n", first_order.total_price);
printf("\nItens do Pedido:\n");
for (int j = 0; j < first_order.num_items; j++) {
printf("- %d x %s\n", first_order.items[j].quantity,
first_order.items[j].item_name);
}
printf("----------------------------\n");
} else {
printf(ANSI_COLOR_GREEN "Não há pedidos na fila de espera"
ANSI_COLOR_RESET);
}
}
void remove_first_waiting_order(Order *waiting_queue, int *waiting_queue_size) {
if (*waiting_queue_size > 0) {
for (int i = 0; i < *waiting_queue_size - 1; i++) {
waiting_queue[i] = waiting_queue[i + 1];
}
(*waiting_queue_size)--;
}
}
void show_ready_stack_items(Order *ready_stack, int ready_stack_top, MenuItem
*menu, int menu_size) {
printf("\n------Comprovantes------\n");
if (ready_stack_top >= 0) {
for (int i = 0; i <= ready_stack_top; i++) {
printf("\nNúmero do pedido: %d\n", i + 1);
printf("Cliente: %s\n", ready_stack[i].customer_name);
printf("-----Endereço------\n");
printf("Cidade: %s\n", ready_stack[i].address->cidade);
printf("Bairro: %s\n", ready_stack[i].address->bairro);
printf("Número da casa: %s\n", ready_stack[i].address->numero_casa);
printf("Complemento: %s\n", ready_stack[i].address->complemento);
printf("------------");
printf("Total: R$%.2f\n", ready_stack[i].total_price);
printf("Itens do Pedido:\n");
for (int j = 0; j < ready_stack[i].num_items; j++) {
printf("- %d x %s\n", ready_stack[i].items[j].quantity,
ready_stack[i].items[j].item_name);
}
printf("----------------------------\n");
}
} else {
printf("Não há pedidos prontos.\n");
}
}
void clear_ready_stack(int ready_stack_top) {
ready_stack_top = -1;
printf(ANSI_COLOR_GREEN "Pedidos prontos foram removidos.\n"
ANSI_COLOR_RESET);
}
int main(void){ // AINDA É NECESSÁRIO LIMPAR A MEMÓRIA DE UMA FORMA EM
QUE O PROGRAMA NÃO SEJA AFETADO
MenuItem *menu = malloc(MAX_ITEMS * sizeof(MenuItem));
int menu_size = MAX_ITEMS;
if (menu == NULL) {
printf(ANSI_COLOR_RED "Erro ao alocar memória para o cardápio.\n"
ANSI_COLOR_RESET);
return 1;
}
for (int i = 0; i < MAX_ITEMS; i++) {
menu[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
if (menu[i].name == NULL) {
printf(ANSI_COLOR_RED "Erro ao alocar memória para os nomes dos itens
do cardápio.\n" ANSI_COLOR_RESET);
return 1;
}
}
strcpy(menu[0].name, "Cerveja Amanteigada");
menu[0].price = 10.0;
strcpy(menu[1].name, "Sorvete de Abóbora");
menu[1].price = 8.0;
strcpy(menu[2].name, "Torta de Abóbora");
menu[2].price = 15.0;
strcpy(menu[3].name, "Feijões de Todos os Sabores");
menu[3].price = 12.0;
strcpy(menu[4].name, "Sapos de Chocolate");
menu[4].price = 6.0;
strcpy(menu[5].name, "Suco de Abóbora");
menu[5].price = 5.0;
strcpy(menu[6].name, "Bife de Dragão");
menu[6].price = 20.0;
strcpy(menu[7].name, "Cupcake de Canário com asas de Fada");
menu[7].price = 7.0;
strcpy(menu[8].name, "Bebida de Fogo");
menu[8].price = 8.0;
strcpy(menu[9].name, "Pimentões Recheados com Molho Picante");
menu[9].price = 18.0;
strcpy(menu[10].name, "Sorvete de Língua de Sapo");
menu[10].price = 9.0;
Order waiting_queue[MAX_QUEUE_SIZE];
Order ready_stack[MAX_QUEUE_SIZE];
int waiting_queue_size = 0;
int ready_stack_top = -1;
int choice;
do{
printf("\nDelivery do Harry\n");
printf("1. Adicionar Pedido\n");
printf("2. Adicionar pedido pronto\n");
printf("3. Mostrar pedidos em espera\n");
printf("4. Mostrar Comprovantes\n");
printf("5. Limpar Comprovantes\n");
printf("6. Sair\n");
printf("Escolha uma opção: ");
scanf("%d", &choice);
switch(choice){
case 1:
break;
make_order(waiting_queue, menu, menu_size, &waiting_queue_size);
case 2:
move_order_to_ready_stack(waiting_queue, ready_stack,
waiting_queue_size, &ready_stack_top);
remove_first_waiting_order(waiting_queue, &waiting_queue_size);
break;
case 3:
show_first_waiting_order(waiting_queue, waiting_queue_size, menu,
menu_size);
break;
case 4:
break;
show_ready_stack_items(ready_stack,ready_stack_top,menu,menu_size);
case 5:
clear_ready_stack(ready_stack_top);
break;
case 6:
printf(ANSI_COLOR_GREEN "Você saiu do programa\n"
ANSI_COLOR_RESET);
break;
default:
printf(ANSI_COLOR_RED "Opção inválida"ANSI_COLOR_RESET);
}
}while(choice !=6);
}
