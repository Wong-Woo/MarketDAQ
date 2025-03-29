echo "Build MarketDAQ..."

echo "Select type of executable binary."
echo "1. RELEASE"
echo "2. TEST_IMGUI"
echo "3. TEST_CURL"

read TYPE_BINARY

if [ "$TYPE_BINARY" = "RELEASE" ] || [ "$TYPE_BINARY" = "1" ]; then
    echo "Build RELEASE..."
    rm -rf build/*
    cmake -DRELEASE=ON -B build/
    cmake --build build/
fi

if [ "$TYPE_BINARY" = "TEST_IMGUI" ] || [ "$TYPE_BINARY" = "2" ]; then
    echo "Build TEST_IMGUI..."
    rm -rf build/*
    cmake -DTEST_IMGUI=ON -B build/
    cmake --build build/
fi

if [ "$TYPE_BINARY" = "TEST_CURL" ] || [ "$TYPE_BINARY" = "3" ]; then
    echo "Build TEST_CURL..."
    rm -rf build/*
    cmake -DTEST_CURL=ON -B build/
    cmake --build build/
fi