CXX = FCCpx
CXXFLAGS = -Kfast -KA64FX -Kopenmp -Nlst=t \
		   -Ksimd -Krestp=all \
		   -Kassume=memory_bandwidth \
           -Kzfill=100 -Kprefetch_sequential=soft \
           -Kprefetch_line=8 -Kprefetch_line_L2=16

TARGET = stream_triad.exe

$(TARGET):
	$(CXX) $(CXXFLAGS) stream_triad.cpp -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) *.lst
