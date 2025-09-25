![Win RELEASE](https://github.com/Wong-Woo/MarketDAQ/actions/workflows/build-windows.yml/badge.svg)
![Linux RELEASE](https://github.com/Wong-Woo/MarketDAQ/actions/workflows/build-linux.yml/badge.svg)

# MarketDAQ

MarketDAQ is a C++ application for visualizing and analyzing time series market data, including stock prices, global macro-economic data, and financial news. Built with ImGui for cross-platform GUI support and designed with a modular MVC architecture.

## Features

- **Real-time Data Visualization**: Interactive charts and graphs for market data analysis
- **Multi-Data Source Support**: Stock data, global macro data, and news data integration
- **Cross-Platform**: Supports Windows and Linux with platform-specific backends
- **Modular Architecture**: Clean separation of Model, View, and Controller components
- **Multiple Build Configurations**: Release build and various test modules

## Project Structure

```
MarketDAQ/
├── src/
│   ├── main.cpp                    # Application entry point
│   ├── model/                      # Data models
│   │   ├── stock_data.*           # Stock market data handling
│   │   ├── global_macro_data.*    # Global macro-economic data
│   │   └── news_data.*            # Financial news data
│   ├── view/                      # UI components
│   │   ├── imgui_backend/         # Platform-specific GUI backends
│   │   └── imgui_frontend/        # UI layout and components
│   ├── controller/                # Business logic
│   │   └── update.*               # Data update controllers
│   └── common/                    # Shared utilities
│       ├── math/                  # Mathematical utilities
│       └── timeconv/              # Time conversion utilities
├── lib/                           # External libraries (curl, imgui, json)
├── test/                          # Unit tests
├── data/                          # Data files
├── doc/                           # Documentation
└── include/                       # Header files
```

## Dependencies

- **CMake** (≥ 3.10)
- **C++17** compiler
- **ImGui** - For GUI rendering
- **cURL** - For HTTP requests and data fetching
- **nlohmann/json** - For JSON parsing

## Building

### Quick Build (Linux/macOS)

```bash
# Interactive build script
./build.sh

# Or directly specify build type:
echo "1" | ./build.sh  # For RELEASE build
```

### Manual Build

#### Release Build
```bash
mkdir build
cmake -DRELEASE=ON -B build/
cmake --build build/
```

#### Test Builds
```bash
# GUI Test
cmake -DTEST_IMGUI=ON -B build/
cmake --build build/

# Network Test
cmake -DTEST_CURL=ON -B build/
cmake --build build/

# File I/O Test
cmake -DTEST_FSTREAM=ON -B build/
cmake --build build/

# JSON Parsing Test
cmake -DTEST_JSON=ON -B build/
cmake --build build/
```

## Usage

### Running the Application

#### Windows
```cmd
# After building with RELEASE option
./build/MarketDAQ.exe
```

#### Linux
```bash
# After building with RELEASE option
./build/MarketDAQ
```

### Build Options

- **RELEASE**: Full application build with GUI and data processing
- **TEST_IMGUI**: Test ImGui integration
- **TEST_CURL**: Test HTTP/network functionality
- **TEST_FSTREAM**: Test file I/O operations
- **TEST_JSON**: Test JSON data parsing

## Platform Support

- **Windows**: Uses Windows-specific ImGui backend (`imgui_windows.cpp`)
- **Linux**: Uses Linux-specific ImGui backend (`imgui_linux.cpp`)
- **Unicode**: Windows builds use non-Unicode configuration for compatibility

## Development

### Architecture

MarketDAQ follows the Model-View-Controller (MVC) pattern:

- **Model**: Data structures for stocks, macro data, and news
- **View**: ImGui-based frontend with platform-specific backends
- **Controller**: Update logic and data processing
- **Common**: Shared utilities for math and time operations

### Adding New Features

1. Add data models in `src/model/`
2. Implement UI components in `src/view/imgui_frontend/`
3. Add business logic in `src/controller/`
4. Create tests in `test/` directory

### Testing

Run individual test modules:
```bash
./build/test_imgui      # GUI tests
./build/test_curl       # Network tests
./build/test_fstream    # File I/O tests
./build/test_json       # JSON parsing tests
```

## Contributing

1. Fork the repository
2. Create your feature branch
3. Add tests for new functionality
4. Ensure all builds pass
5. Submit a pull request

## License

[Add your license information here]