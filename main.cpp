/*
 *  typedef of a vector of class can have a constructor as i find
 *  out from this piece of code. Can someone explain how! Check
 *  this line - m_layers.push_back(Layer());
 */

#include <vector>
#include <iostream>
#include <iomanip>

class Neuron {
public:
  Neuron(uint32_t ly = 0, uint32_t nr = 0)
  : layer { ly }, number { nr } {
    this_inst = ++instance;
    ctor = '+';
    std::cout << "+ Neuron constructor - Instance/Layer/Nr./ctor: "
              << std::setw(3) << this_inst
              << '/' << layer << '/' << number << '/'
              << ctor
              << '\n';
  }

  Neuron(Neuron const & that) {
    layer = that.layer;
    number = that.number;
    this_inst = that.this_inst;
    ctor = 'c';
    std::cout << "+ Neuron copy ctor   - Instance/Layer/Nr./ctor: "
              << std::setw(3) << this_inst
              << '/' << layer << '/' << number << '/'
              << ctor
              << '\n';
  };

  Neuron(Neuron && that) {
    layer = std::move(that.layer);
    number = std::move(that.number);
    this_inst = std::move(that.this_inst);
    ctor = '-';
    std::cout << "+ Neuron move ctor   - Instance/Layer/Nr./ctor: "
              << std::setw(3) << this_inst
              << '/' << layer << '/' << number << '/'
              << ctor
              << '\n';
  }

  Neuron const & operator=(Neuron const &) = delete;

  virtual
  ~Neuron() {
    std::cout << "- Neuron destructor  - Instance/Layer/Nr./ctor: "
              << std::setw(3) << this_inst
              << '/' << layer << '/' << number << '/'
              << ctor
              << '\n';
    layer = 0;
    number = 0;
  }

private:
  uint32_t layer;
  uint32_t number;
  static
  uint64_t instance;
  uint64_t this_inst;
  char ctor;
};

uint64_t Neuron::instance { 0 };

//typedef std::vector<Neuron> Layer;
using Layer = std::vector<Neuron>;

class Net {
public:
  Net(std::vector<unsigned> & topology);
  void feedForward(const std::vector<double> & inputVals) {}
  void backProp(const std::vector<double> & targetVals) {}
  void getResults(std::vector<double> & resultVals) {}

private:
  std::vector<Layer> m_layers;    // m_layers[layerNum][neuronNum]
};

Net::Net(std::vector<unsigned> & topology) {
  unsigned numLayer = topology.size();
  for (unsigned layerNum = 0; layerNum < numLayer; ++layerNum) {
    m_layers.push_back(Layer());
    // we create a new Layer. Fill it with Neuron and
    // add a bias Neuron to the Layer
    for (unsigned neuronNum = 0;
         neuronNum <= topology[layerNum];
         ++neuronNum) {
      std::cout << "making a Neuron" << '\n';
      m_layers.back().push_back(Neuron(layerNum, neuronNum));
      std::cout << "we made a Neuron" << '\n';
    }
  }
}

int main() {
  std::vector<unsigned> topology;

  topology.push_back(3);
  topology.push_back(2);
  topology.push_back(1);

  Net myNet(topology);
  std::vector<double> inputVals;
  myNet.feedForward(inputVals);

  std::vector<double> targetVals;
  myNet.backProp(targetVals);

  std::vector<double> resultVals;
  myNet.getResults(resultVals);
}