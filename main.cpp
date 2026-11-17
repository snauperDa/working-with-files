/******************************
* Работа с файлами            *
* Вариант 10                  *
* Колосков Дмитрий Викторович *
******************************/

#include <iostream>
#include <fstream>
#include <cmath>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Car {
  string brand;
  int year;
  string owner;
  string plateNumber;
};

vector<string> splitFields(const string& line) {
  vector<string> fields;
  size_t start = 0;

  while (true) {
    size_t separator = line.find(';', start);

    if (separator == string::npos) {
      fields.push_back(line.substr(start));
      break;
    }

    fields.push_back(line.substr(start, separator - start));
    
    start = separator + 1;
  }

  return fields;
}

bool readInt(const string& text, int& value) {
  istringstream parser(text);
  char extra;

  if (!(parser >> value) || !isfinite(value)) {
    return false;
  }

  return !(parser >> extra);
}

int main () {
  string lineFile;
  int countLineFile = 0;
  int sumAgeCar = 0;
  vector<Car> carsGarage;
  vector<string> fields;
  Car tempCar;
  string brandCar;

  ifstream file("text.txt");

  if (!file.is_open()) {
    cout << "INVALID: file not found";
    return 1;
  }

  cout << "All the cars in the garage\n";

  while (getline(file, lineFile)) {
    fields = splitFields(lineFile);

    if (fields.size() != 4) {
      continue;
    }

    tempCar.brand       = fields[0];

    if (!readInt(fields[1], tempCar.year)) {
      continue;
    }

    tempCar.owner       = fields[2];
    tempCar.plateNumber = fields[3];

    cout << tempCar.brand       << '\t' << tempCar.owner << '\t'
         << tempCar.plateNumber << '\t' << tempCar.year  << '\n';

    carsGarage.push_back(tempCar);
  }

  int oldYearCar = carsGarage[0].year;
  for (const auto& element: carsGarage) {
    if (element.year < oldYearCar) {
        oldYearCar = element.year;
    }
  }

  cout << "\nThe oldest car from year " << oldYearCar
       << "\n\nEnter the car brand you are interested in\n";
  
  getline(cin, brandCar);

  for (const auto& car : carsGarage) {
    if (car.brand == brandCar) {
      cout << car.brand << '\t' << car.owner << '\t'
           << car.plateNumber << '\t' << car.year << '\n';

      ++countLineFile;
      sumAgeCar += 2026 - car.year;
    }
  }

  if (countLineFile == 0) {
    cout << "No cars of this brand\n";
  } else {
    cout << "Average age: " << fixed << setprecision(2)
         << static_cast<double>(sumAgeCar) / countLineFile << " years\n";
  }

}