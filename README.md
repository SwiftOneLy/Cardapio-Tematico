# Cardapio-Tematico


Um sistema simples em C que simula o gerenciamento de pedidos de um **serviço de delivery temático**, inspirado no universo do Harry Potter.  
O programa utiliza **fila de espera** e **pilha de pedidos prontos**, além de oferecer opções de pagamento e exibir comprovantes.

---

## 🧠 Sobre o Projeto

Este projeto foi desenvolvido como parte dos estudos em **Ciência da Computação (UNICID)**, com o objetivo de aplicar conceitos de **estruturas de dados**, como:
- Filas (`queue`)
- Pilhas (`stack`)
- Alocação dinâmica de memória (`malloc`, `realloc`, `free`)
- Estruturação modular e funções auxiliares em C

---

## 📋 Funcionalidades

✅ Adicionar um novo pedido  
✅ Listar todos os pedidos em espera  
✅ Mover pedido da fila para a pilha de prontos  
✅ Exibir comprovantes de pedidos prontos  
✅ Limpar os comprovantes  
✅ Sair do programa  

---

## 🖥️ Estrutura de Dados Utilizadas

| Estrutura | Tipo | Função |
|------------|------|--------|
| `Order` | Struct | Representa um pedido completo |
| `OrderItem` | Struct | Representa um item do pedido |
| `Address` | Struct | Guarda informações do endereço do cliente |
| `MenuItem` | Struct | Representa um item do cardápio |
| `waiting_queue[]` | Fila (array) | Armazena pedidos em espera |
| `ready_stack[]` | Pilha (array) | Armazena pedidos prontos |

---

## ⚙️ Como Executar

### 🔧 Pré-requisitos
- Ter o compilador **GCC** instalado  
  *(Linux, macOS ou Windows com MinGW / Code::Blocks)*


```bash

📚 Exemplo de Execução
===== DELIVERY DO HARRY =====
1. Adicionar Pedido
2. Adicionar Pedido Pronto
3. Mostrar Pedidos em Espera
4. Mostrar Comprovantes
5. Limpar Comprovantes
6. Sair
Escolha uma opção: 1

------ FAZER PEDIDO ------
Nome do cliente: Felippe
Cidade (sigla do estado, ex: SP): SP
Bairro: Centro
Rua: Principal
Número: 123
Complemento: 
----- CARDÁPIO -----
1. Cerveja Amanteigada - R$10.00
2. Sorvete de Abóbora - R$8.00
...
Número do item: 1
Quantidade: 2
Deseja adicionar outro item? (s/n): n
----- Forma de Pagamento -----
1. Crédito
2. Débito
3. Pix
Escolha: 3
Pedido adicionado à fila de espera com sucesso!


