

# PokeBatalha

PokeBatalha é um jogo simples de batalha de Pokémon em C, onde dois jogadores ou um jogador e uma IA competem usando seus Pokémon. O objetivo é derrotar todos os Pokémon do adversário utilizando ataques, itens e estratégias de tipo.

**Esse projeto é uma versão atualizada de um projeto antigo que também simulava uma batalha Pokemon, é possível conferir a versão antiga [aqui](https://github.com/marcoreliog/Simulacao-Pokemon)** 

**Autor**: Marco Aurélio Gonçalves de Souza, Estudante de Engenharia de Computação


**Instituição**: Universidade Federal de Minas Gerais

## Funcionalidades

- **Batalha entre Pokémon**: Dois jogadores ou um jogador contra a IA, com batalhas baseadas em ataques e itens.
- **Ataques e Tipos**: Cada Pokémon possui um tipo (fogo, água, pedra, etc.), e o tipo de ataque tem uma vantagem ou desvantagem contra outro tipo.
- **Itens**: O jogador pode usar poções e outros itens durante a batalha para curar ou reviver seu Pokémon.
- **Barra de Vida**: A vida dos Pokémon é representada por uma barra visual, com cores que variam de verde (saudável) a vermelho (perto de ser derrotado).
- **Sistema de Níveis e Experiência**: Os Pokémon ganham experiência e podem subir de nível durante a batalha.

## Requisitos

- Sistema operacional: Linux, macOS ou Windows (com compilador C)
- Compilador C: GCC ou qualquer outro compilador compatível com C.
- Biblioteca `unistd.h` (usada para funções de controle de tempo).

## Como rodar o jogo

1. **Clone o repositório**:
   
   ```bash
   git clone https://github.com/marcoreliog/PokeBatalha.git
   cd PokeBatalha
   ```

2. **Compile o código**:
   
   ```bash
   gcc -o poke_batalha poke_batalha.c
   ```

3. **Execute o jogo**:
   
   ```bash
   ./poke_batalha
   ```

## Como funciona o código

1. **Estruturas de Dados**:
   - `Pokemon`: Representa um Pokémon com atributos como nome, tipo, vida, ataque, defesa, nível e experiência.
   - `Inventario`: Representa o inventário de itens do jogador (poções, super poções, reviver).
   
2. **Sistema de Combate**:
   - O jogo inicia com a escolha de uma ação: atacar, usar um item ou trocar Pokémon.
   - O dano é calculado com base nos atributos dos Pokémon (ataque e defesa) e nas vantagens de tipo.
   - O jogador pode usar itens para curar ou reviver seus Pokémon durante a batalha.

3. **IA do oponente**:
   - O Jogador 2 é controlado por uma IA simples que usa poções quando a vida do Pokémon está baixa e ataca de forma direta.

4. **Leitura de Arquivo**:
   - O código lê os dados dos Pokémon a partir de um arquivo de texto (`teste.txt`). Este arquivo contém informações sobre os Pokémon de cada jogador (nome, ataque, defesa, vida e tipo).

## Exemplo de Arquivo de Dados (teste.txt)

```txt
2 2
Squirtle 10 5 15 agua
Bulbasaur 8 6 14 grama
Pikachu 12 4 10 eletrico
Charmander 10 5 14 fogo
```

### Explicação do formato do arquivo:

- O arquivo começa com dois números, N e M, que indicam quantos Pokémon cada jogador possui.
- A seguir, há uma lista de Pokémon de cada jogador, com informações sobre nome, ataque, defesa, vida e tipo.

## Personalizações

- **Adicionar mais Pokémon**: Para adicionar mais Pokémon, basta editar o arquivo `teste.txt` com novos Pokémon, seguindo o formato acima.
- **Modificar Atributos**: Você pode modificar os atributos de ataque, defesa, vida e tipos dos Pokémon diretamente no código ou no arquivo `teste.txt`.
- **Melhorar IA**: A IA pode ser melhorada para fazer escolhas mais estratégicas, como usar ataques poderosos dependendo do tipo do oponente ou trocar de Pokémon.

## Contribuições

Contribuições são bem-vindas! Se você encontrar um bug ou quiser melhorar o jogo, sinta-se à vontade para abrir um *pull request*.

