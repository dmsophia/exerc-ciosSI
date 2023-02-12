#include <iostream>
using namespace std;

// Definição do esquema de clientes que serão utilizados na tabela hash
class Cliente
{
private:
  int imei;
  string login;

public:
  Cliente();
  Cliente(int imei, string login);
  string getLogin() const;
  int getImei() const;
};
Cliente::Cliente()
{
  this->imei = -1;
  this->login = "";
};
Cliente::Cliente(int imei, string login) // Define que as propriedades da classe se tornem os atributos de sua criação
{
  this->imei = imei;
  this->login = login;
}
string Cliente::getLogin() const
{
  return login;
}
int Cliente::getImei() const
{
  return imei;
}
// define as propriedades da hash que será utilizada para realizar a tabela, como, por exemplo, o número máximo da chave do hash
class Hash
{
public:
  Hash(int max_items = 100);
  ~Hash();
  bool isFull() const;
  int getLength() const;
  // definição das ações possíveis a se realizar com tabela hash (busca, inserção e remoção)
  void retrieveItem(Cliente &cliente, bool &found);
  void insertItem(Cliente cliente);
  void deleteItem(Cliente cliente);
  void print();

private:
  int getHash(Cliente cliente);
  int max_items;
  int length;
  Cliente *structure;
};
// Mesma funcionalidade acima em Cliente::Cliente (Define que as propriedades da classe se tornem os atributos de sua criação)
Hash::Hash(int max)
{
  length = 0;
  max_items = max;
  structure = new Cliente[max_items];
}
// Métodos da classe Hash que serão usados na tabela hash

Hash::~Hash()
{
  delete[] structure;
}

bool Hash::isFull() const
{
  return (length == max_items);
}

int Hash::getLength() const
{
  return length;
}
// Método que busca na tabela hash um cliente, retornando um booleano verdadeiro, ou seja, um cliente, ou falso, caso esse não exista
void Hash::retrieveItem(Cliente &cliente, bool &found)
{
  int location = getHash(cliente);
  Cliente aux = structure[location];
  if (cliente.getImei() != aux.getImei())
  {
    found = false;
  }
  else
  {
    found = true;
    cliente = aux;
  }
}
// Método que insere um cliente na tabela hash, definindo sua localização
void Hash::insertItem(Cliente cliente)
{
  int location = getHash(cliente);
  structure[location] = cliente;
  length++;
}
// Método que deleta um cliente, encontrando sua localização e deletando-o
void Hash::deleteItem(Cliente cliente)
{
  int location = getHash(cliente);
  structure[location] = Cliente();
  length--;
}
// Método que realiza um for para mostrar todos os elementos e "linhas" dentro da tabela
void Hash::print()
{
  for (int i = 0; i < max_items; i++)
  {
    cout << i << ":" << structure[i].getImei() << ", " << structure[i].getLogin() << endl;
  }
}
// Função da tabela hash, que realiza a função mod a partir do número imei fornecido e de uma chave hash inserida
int Hash::getHash(Cliente cliente)
{
  return cliente.getImei() % max_items;
}
// Casos de teste
int main()
{
  // Caso de teste 1:
  // Definição de imeis e logins que serão inseridos na tabela hash em dois arrays
  Hash clientesHash = Hash(97);
  int imeis[7] = {
      12704, 31300, 1234,
      49001, 52202, 65606,
      91234};
  string logins[7] = {
      "Pedro", "Raul", "Paulo",
      "Carlos", "Lucas", "Maria",
      "Samanta"};
  // Loop em cada imei e logins dos arrays para adicioná-los na tabela hash, que vai de 0 a 96
  for (int i = 0; i < 7; i++)
  {
    Cliente cliente = Cliente(imeis[i], logins[i]);
    clientesHash.insertItem(cliente);
  }
  clientesHash.print();
  cout << "------------------------------" << endl;

  // Caso de teste 2:
  // Busca de um cliente a partir de seu imei
  Cliente cliente(12704, "");
  bool found = false;
  clientesHash.retrieveItem(cliente, found);
  cout << cliente.getLogin() << " -> " << found << endl;

  cout << "------------------------------" << endl;

  // Caso de teste 3:
  // Remoção de um cliente que existe na tabela
  clientesHash.deleteItem(cliente);
  clientesHash.print();
  cout << "Fim" << endl;
  cout << "------------------------------" << endl;

  // Caso de teste 4:
  // Remoção de um cliente que não existe
  Cliente cliente2(34567, "");
  bool found2 = false;
  clientesHash.retrieveItem(cliente2, found2);
  cout << cliente2.getLogin() << " -> " << found2 << endl;
  cout << "------------------------------" << endl;

  // Caso de teste 5:
  // Inserção de um único novo cliente
  Cliente novoCliente = Cliente(56789, "Sophia");
  clientesHash.insertItem(novoCliente);
  clientesHash.print();
  return 0;
}