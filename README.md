# 🚗 VehicleUserManagementSuite (C++)
A capable C++ console app that manages **users**, **vehicles**, and a **manager profile** with plain-text storage and a clean CLI. ✨
## ✨ Features
- 👤 **Users:** add, list (name, national code, password)
- 🚘 **Vehicles:** add, list (code, brand, model, capacity)
- 🔗 **Assign:** link vehicles to users
- 🧑‍💼 **Manager:** save manager info
- 💾 **Persistence:** `users.txt`, `vehicles.txt`, `manager.txt`
- 📊 **Tables:** neat fixed-width output (`iomanip`)

## ▶️ Quick Start
```bash
# build (if headers are in folders 'models' & 'utils')
g++ -std=c++17 main.cpp -Imodels -Iutils -o license-center

# OR if includes were changed to root paths
# g++ -std=c++17 main.cpp -o license-center

# run
./license-center   # Windows: .\license-center.exe
