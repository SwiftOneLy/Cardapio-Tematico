
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ======================== CORES PARA TERMINAL ===============================
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

// ======================== CONSTANTES ========================================
#define MAX_NAME_LENGTH 100
#define MAX_MENU_ITEMS 10
#define MAX_QUEUE 100
#define MAX_STACK 100

// ======================== ESTRUTURAS DE DADOS ===============================
typedef struct {
    char cidade[MAX_NAME_LENGTH];
    char bairro[MAX_NAME_LENGTH];
    char rua[MAX_NAME_LENGTH];
    int numero;
    char complemento[MAX_NAME_LENGTH];
} Address;

typedef struct {
    char item_name[MAX_NAME_LENGTH];
    int quantity;
} OrderItem;

typedef struct {
    int order_number;
    char client_name[MAX_NAME_LENGTH];
    Address address;
    OrderItem *items;
    int num_items;
    float total;
    char payment_method[20];
} Order;

typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

// ======================== FUNÇÕES AUXILIARES ================================
bool is_Cidade_Valid(char *cidade) {
    // Aceita apenas siglas de estados brasileiros
    const char *valid_states[] = {
        "AC","AL","AP","AM","BA","CE","DF","ES","GO","MA",
        "MT","MS","MG","PA","PB","PR","PE","PI","RJ","RN",
        "RS","RO","RR","SC","SP","SE","TO"
    };
    for (int i = 0; i < 27; i++) {
        if (strcasecmp(cidade, valid_states[i]) == 0) return true;
    }
    return false;
}

void print_menu(MenuItem menu[], int menu_size) {
    printf("\n----- CARDÁPIO -----\n");
    for (int i = 0; i < menu_size; i++)
        printf("%d. %s - R$%.2f\n", i + 1, menu[i].name, menu[i].price);
}

void initialize_menu(MenuItem menu[], int *menu_size) {
    *menu_size = 5;
    strcpy(menu[0].name, "Cerveja Amanteigada");
    menu[0].price = 10.00;
    strcpy(menu[1].name, "Sorvete de Abóbora");
    menu[1].price = 8.00;
    strcpy(menu[2].name, "Torta de Abóbora");
    menu[2].price = 15.00;
    strcpy(menu[3].name, "Feijões de Todos os Sabores");
    menu[3].price = 12.00;
    strcpy(menu[4].name, "Suco de Abóbora");
    menu[4].price = 7.50;
}

Address make_address() {
    Address address;
    do {
        printf("Cidade (sigla do estado, ex: SP): ");
        scanf("%s", address.cidade);
        if (!is_Cidade_Valid(address.cidade))
            printf(ANSI_COLOR_RED "Estado inválido! Tente novamente.\n" ANSI_COLOR_RESET);
    } while (!is_Cidade_Valid(address.cidade));

    printf("Bairro: ");
    scanf(" %[^\n]", address.bairro);
    printf("Rua: ");
    scanf(" %[^\n]", address.rua);
    printf("Número: ");
    scanf("%d", &address.numero);
    printf("Complemento (opcional): ");
    scanf(" %[^\n]", address.complemento);

    return address;
}

OrderItem *add_items_to_order(MenuItem menu[], int menu_size, int *num_items, float *total) {
    int choice, quantity;
    OrderItem *items = NULL;
    char continue_choice;

    *total = 0;
    *num_items = 0;

    do {
        print_menu(menu, menu_size);
        printf("Número do item: ");
        scanf("%d", &choice);

        if (choice < 1 || choice > menu_size) {
            printf(ANSI_COLOR_RED "Opção inválida!\n" ANSI_COLOR_RESET);
            continue;
        }

        printf("Quantidade: ");
        scanf("%d", &quantity);

        items = realloc(items, (*num_items + 1) * sizeof(OrderItem));
        strcpy(items[*num_items].item_name, menu[choice - 1].name);
        items[*num_items].quantity = quantity;

        *total += menu[choice - 1].price * quantity;
        (*num_items)++;

        printf("Deseja adicionar outro item? (s/n): ");
        scanf(" %c", &continue_choice);
    } while (continue_choice == 's' || continue_choice == 'S');

    return items;
}

void make_order(Order *waiting_queue, MenuItem menu[], int menu_size, int *waiting_queue_size) {
    Order new_order;
    printf("\n------ FAZER PEDIDO ------\n");
    printf("Nome do cliente: ");
    scanf(" %[^\n]", new_order.client_name);
    new_order.address = make_address();
    new_order.items = add_items_to_order(menu, menu_size, &new_order.num_items, &new_order.total);
    new_order.order_number = *waiting_queue_size + 1;

    int payment_choice;
    printf("\n----- Forma de Pagamento ------\n1. Crédito\n2. Débito\n3. Pix\nEscolha: ");
    scanf("%d", &payment_choice);
    switch (payment_choice) {
        case 1: strcpy(new_order.payment_method, "Crédito"); break;
        case 2: strcpy(new_order.payment_method, "Débito"); break;
        case 3: strcpy(new_order.payment_method, "Pix"); break;
        default: strcpy(new_order.payment_method, "Não informado");
    }

    waiting_queue[*waiting_queue_size] = new_order;
    (*waiting_queue_size)++;

    printf(ANSI_COLOR_GREEN "\nPedido adicionado à fila de espera com sucesso!\n" ANSI_COLOR_RESET);
}

void show_waiting_orders(Order waiting_queue[], int waiting_queue_size) {
    if (waiting_queue_size == 0) {
        printf(ANSI_COLOR_YELLOW "Nenhum pedido em espera.\n" ANSI_COLOR_RESET);
        return;
    }

    printf("\n------ Pedidos em Espera ------\n");
    for (int i = 0; i < waiting_queue_size; i++) {
        printf("Pedido #%d - Cliente: %s - Total: R$%.2f\n",
               waiting_queue[i].order_number,
               waiting_queue[i].client_name,
               waiting_queue[i].total);
    }
}

void move_order_to_ready_stack(Order *waiting_queue, Order *ready_stack, int *waiting_queue_size, int *ready_stack_top) {
    if (*waiting_queue_size == 0) {
        printf(ANSI_COLOR_YELLOW "Nenhum pedido para mover!\n" ANSI_COLOR_RESET);
        return;
    }

    ready_stack[++(*ready_stack_top)] = waiting_queue[0];

    for (int i = 1; i < *waiting_queue_size; i++)
        waiting_queue[i - 1] = waiting_queue[i];

    (*waiting_queue_size)--;

    printf(ANSI_COLOR_GREEN "Pedido movido para a pilha de prontos!\n" ANSI_COLOR_RESET);
}

void show_ready_stack(Order ready_stack[], int ready_stack_top) {
    if (ready_stack_top == -1) {
        printf(ANSI_COLOR_YELLOW "Nenhum pedido pronto.\n" ANSI_COLOR_RESET);
        return;
    }

    printf("\n------ COMPROVANTES ------\n");
    for (int i = 0; i <= ready_stack_top; i++) {
        printf("\nPedido #%d - Cliente: %s\nTotal: R$%.2f\nPagamento: %s\n",
               ready_stack[i].order_number,
               ready_stack[i].client_name,
               ready_stack[i].total,
               ready_stack[i].payment_method);
    }
}

void clear_ready_stack(int *ready_stack_top) {
    *ready_stack_top = -1;
    printf(ANSI_COLOR_GREEN "Comprovantes limpos!\n" ANSI_COLOR_RESET);
}

// ======================== FUNÇÃO PRINCIPAL ==================================
int main() {
    Order waiting_queue[MAX_QUEUE];
    Order ready_stack[MAX_STACK];
    int waiting_queue_size = 0;
    int ready_stack_top = -1;
    MenuItem menu[MAX_MENU_ITEMS];
    int menu_size = 0;

    initialize_menu(menu, &menu_size);

    int choice;
    do {
        printf("\n\n===== DELIVERY DO HARRY =====\n");
        printf("1. Adicionar Pedido\n");
        printf("2. Adicionar Pedido Pronto\n");
        printf("3. Mostrar Pedidos em Espera\n");
        printf("4. Mostrar Comprovantes\n");
        printf("5. Limpar Comprovantes\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: make_order(waiting_queue, menu, menu_size, &waiting_queue_size); break;
            case 2: move_order_to_ready_stack(waiting_queue, ready_stack, &waiting_queue_size, &ready_stack_top); break;
            case 3: show_waiting_orders(waiting_queue, waiting_queue_size); break;
            case 4: show_ready_stack(ready_stack, ready_stack_top); break;
            case 5: clear_ready_stack(&ready_stack_top); break;
            case 6: printf(ANSI_COLOR_CYAN "Saindo do programa...\n" ANSI_COLOR_RESET); break;
            default: printf(ANSI_COLOR_RED "Opção inválida!\n" ANSI_COLOR_RESET);
        }
    } while (choice != 6);

    return 0;
}
