#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  // Para medir o tempo de execução

#define MAX_PRODUCTS 10000  // Número de produtos
#define MAX_NAME_LENGTH 50 // Tamanho máximo do nome do produto

// Estrutura que representa um produto no e-commerce
typedef struct {
    int id;                  // ID único do produto
    char name[MAX_NAME_LENGTH];  // Nome do produto
    float price;             // Preço do produto
} Product;

// Lista de nomes de produtos reais para e-commerce
const char *productNames[] = {
    "Smartphone Samsung Galaxy",
    "Notebook Dell Inspiron",
    "Geladeira Brastemp Frost Free",
    "Cafeteira Nespresso",
    "Fritadeira Airfryer Mondial",
    "TV LED 50 Polegadas LG",
    "Console Playstation 5",
    "Headset Gamer HyperX",
    "Máquina de Lavar Electrolux",
    "Ventilador Arno Turbo",
    "Teclado Mecânico Razer",
    "Impressora Multifuncional HP",
    "Relógio Smartwatch Apple",
    "Câmera DSLR Canon",
    "Micro-ondas Panasonic",
    "Bicicleta Caloi Aro 29",
    "Perfume Chanel No 5",
    "Sapato Social Masculino",
    "Bolsa Feminina de Couro",
    "Óculos de Sol Ray-Ban",
    "Tablet Samsung Galaxy Tab",
    "Aspirador de Pó Robô Roomba",
    "Monitor Curvo Samsung 27",
    "Geladeira Side by Side LG",
    "Smart Speaker Amazon Echo",
    "Patinete Elétrico Xiaomi",
    "Cervejeira Consul 82 Litros",
    "Tênis Esportivo Nike Air Max",
    "Mouse Gamer Logitech G502",
    "Carregador Rápido Anker",
    "Mochila Anti-furto Samsonite",
    "Churrasqueira Elétrica Cadence",
    "Drone DJI Mavic Air 2",
    "Projetor Epson Full HD",
    "SSD Externo Samsung T7",
    "Fone de Ouvido Bluetooth Sony",
    "Smartwatch Xiaomi Mi Band",
    "Fogão 4 Bocas Consul",
    "Liquidificador Osterizer Pro",
    "Pipoqueira Elétrica Britânia",
    "Torradeira Philips Walita",
    "Cadeira Gamer ThunderX3",
    "Barbeador Elétrico Philips",
    "Caixa de Som Bluetooth JBL",
    "Smart TV OLED Sony 55",
    "Ar Condicionado Split Samsung",
    "Câmera de Segurança Intelbras",
    "Placa de Vídeo Nvidia RTX 3080",
    "Notebook Apple MacBook Pro",
    "Cama Box Casal Ortobom",
    "Ferro de Passar Philips",
    "Jogo de Panelas Tramontina",
    "Roteador Mesh TP-Link",
    "Piano Digital Yamaha",
    "Toca-discos Vinil Audio-Technica",
    "Máquina de Café Espresso Oster",
    "Lava-Louças Brastemp 10 Serviços",
    "Desumidificador de Ar Gree",
    "Secador de Cabelo Taiff",
    "Batedeira Planetária KitchenAid",
    "Home Theater LG 5.1",
    "Caixa Organizadora Sanremo",
    "Espremedor de Frutas Mondial",
    "Grill George Foreman",
    "Purificador de Água Europa",
    "Bicicleta Ergométrica Kikos",
    "Piscina Inflável 3000 Litros",
    "Tapete Higiênico para Pets",
    "Estante de Livros Artely",
    "Cortador de Grama Tramontina",
    "Kit Ferramentas Bosch 100 Peças",
    "Cortina Blackout Bella Janela",
    "Console Nintendo Switch",
    "Chinelo Havaianas Tradicional",
    "Prancha de Surf 6' Al Merrick",
    "Roupão de Banho Buddemeyer",
    "Carrinho de Bebê Galzerano",
    "Chaleira Elétrica Philco",
    "Panela de Pressão Elétrica Electrolux",
    "Tapete de Yoga ProLite",
    "Relógio Garmin Forerunner",
    "Brinquedo Lego Star Wars",
    "Secadora de Roupas Brastemp",
    "Luminária LED Philips",
    "Carrinho de Compras Dobrável",
    "Suporte para Notebook Nulaxy",
    "Mixer de Mão Mondial",
    "Copo Térmico Stanley 500ml",
    "Mala de Viagem Samsonite",
    "Sapatilha Feminina Moleca",
    "Kit Lâmpadas Inteligentes Positivo",
    "Smartphone Xiaomi Poco X3",
    "Tênis Adidas Ultraboost",
    "Canivete Suíço Victorinox",
    "Câmera GoPro Hero 9",
    "Monitor UltraWide LG 34",
    "Suporte para TV Multivisão",
    "Frigobar Consul Retrô",
    "Conjunto de Malas Samsonite",
    "Jaqueta Corta Vento Nike",
    "Cinta Elástica Abdominal",
    "Forno Elétrico Philco",
    "Máquina de Costura Singer",
    "Cadeira de Escritório Ergonômica",
    "Purificador de Água Consul",
    "Caneca Térmica Yeti",
    "Monitor Gamer 240Hz Alienware",
    "Cafeteira Francesa Bodum",
    "Pipoqueira para Micro-ondas",
    "Árvore de Natal 1,5m Pinheiro",
    "Barra de Som Samsung 320W",
    "Churrasqueira a Gás Weber",
    "Cinto Masculino Couro Fasolo",
    "Chinelo Slide Adidas",
    "Hoverboard Foston",
    "Mochila para Notebook Targus",
    "Espelho Smart LED Touch",
    "Escova Rotativa Philco",
    "Maquininha de Cartão PagSeguro",
    "Coleira Inteligente para Pets",
    "Relógio Invicta Pro Diver",
    "Câmera de Ré Automotiva Pioneer",
    "Lustre Pendente de Cristal",
    "Lente Canon EF 50mm f/1.8",
    "Bola de Futebol Nike Strike",
    "Smartwatch Garmin Fenix 6",
    "Bota Feminina Cano Curto Vizzano",
    "Coqueteleira de Inox Tramontina",
    "Smart TV 4K TCL 55",
    "Cafeteira Italiana Bialetti",
    "Chave de Impacto DeWalt",
    "Óculos de Realidade Virtual Oculus Quest 2",
    "Assento Massageador Shiatsu",
    "Aquecedor a Óleo Mondial",
    "Conjunto Mesa e Cadeiras Tramontina",
    "Maleta de Maquiagem Ruby Rose",
    "Carrinho de Passeio Burigotto",
    "Guarda-roupa 6 portas Henn",
    "Abajur Touch Sensor"
};

// Função para gerar um nome de produto aleatório a partir da lista predefinida
void generateProductName(char *name) {
    int index = rand() % (sizeof(productNames) / sizeof(productNames[0]));
    strncpy(name, productNames[index], MAX_NAME_LENGTH - 1);
    name[MAX_NAME_LENGTH - 1] = '\0'; // Garante que a string termina corretamente
}

// Função para gerar uma lista de produtos com preços aleatórios
void generateProductList(Product products[], int numProducts) {
    for (int i = 0; i < numProducts; ++i) {
        products[i].id = i + 1; // ID sequencial
        generateProductName(products[i].name); // Nome aleatório
        products[i].price = (rand() % 10000) / 100.0; // Preço aleatório entre $0 e $100
    }
}

// Função para imprimir um produto
void printProduct(Product product) {
    printf("ID: %d, Nome: %s, Preço: $%.2f\n", product.id, product.name, product.price);
}

// Função para imprimir a lista de produtos
void printProductList(Product products[], int numProducts) {
    printf("\nLista de produtos gerados:\n");
    for (int i = 0; i < numProducts; ++i) {
        printProduct(products[i]);
    }
}

// Implementação da busca sequencial
int buscaSequencial(Product products[], int numProducts, const char* alvo) {
    for (int i = 0; i < numProducts; ++i) {
        if (strcmp(products[i].name, alvo) == 0) {
            return i; // Retorna a posição do produto se encontrado
        }
    }
    return -1; // Produto não encontrado
}

// Implementação da busca binária
int buscaBinaria(Product products[], int baixo, int alto, const char* alvo) {
    while (baixo <= alto) {
        int meio = baixo + (alto - baixo) / 2; // Calcula o meio da lista
        int comparacao = strcmp(products[meio].name, alvo); // Compara o produto do meio com o alvo

        if (comparacao == 0) {
            return meio; // Produto encontrado
        } else if (comparacao < 0) {
            baixo = meio + 1; // Produto alvo está na parte superior
        } else {
            alto = meio - 1; // Produto alvo está na parte inferior
        }
    }
    return -1; // Produto não encontrado
}

// Função de ordenação para os produtos (usada para a busca binária)
int compareByName(const void* a, const void* b) {
    Product* productA = (Product*)a;
    Product* productB = (Product*)b;
    return strcmp(productA->name, productB->name);
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa a semente para geração de números aleatórios

    Product products[MAX_PRODUCTS]; // Array de produtos
    int numProducts = MAX_PRODUCTS; // Quantidade de produtos a serem gerados
    
    // Gera a lista de produtos
    generateProductList(products, numProducts);
    
    // Imprime a lista de produtos
    printProductList(products, 180); // Exibe apenas os 10 primeiros produtos

    // Define o produto alvo para busca
    char alvo[MAX_NAME_LENGTH] = "Bicicleta Ergométrica Kikos";

    // Medição de tempo da busca sequencial
    printf("\nBusca sequencial pelo produto '%s':\n", alvo);
    clock_t inicioSeq = clock();
    int indexSeq = buscaSequencial(products, numProducts, alvo);
    clock_t fimSeq = clock();
    double tempoSeq = (double)(fimSeq - inicioSeq) / CLOCKS_PER_SEC;

    if (indexSeq != -1) {
        printf("Produto encontrado na posição %d: ", indexSeq);
        printProduct(products[indexSeq]);
    } else {
        printf("Produto não encontrado na busca sequencial.\n");
    }
    printf("Tempo de execução da busca sequencial: %.6f segundos\n", tempoSeq);

    // Ordena a lista de produtos para a busca binária
    qsort(products, numProducts, sizeof(Product), compareByName);

    // Medição de tempo da busca binária
    printf("\nBusca binária pelo produto '%s':\n", alvo);
    clock_t inicioBin = clock();
    int indexBin = buscaBinaria(products, 0, numProducts - 1, alvo);
    clock_t fimBin = clock();
    double tempoBin = (double)(fimBin - inicioBin) / CLOCKS_PER_SEC;
    
    if (indexBin != -1) {
        printf("Produto encontrado na posição %d:", indexBin);
        printProduct(products[indexBin]);
    } else {
        printf("Produto não encontrado na busca binária.\n");
    }
    printf("Tempo de execução da busca binária: %.6f segundos\n", tempoBin);
    

    return 0;
}
