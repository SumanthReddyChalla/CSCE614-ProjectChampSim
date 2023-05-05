./config.sh champsim_config.json
make


bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/437.leslie3d-149B.champsimtrace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/453.povray-252B.champsimtrace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/600.perlbench_s-210B.champsimtrace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/603.bwaves_s-1080B.champsimtrace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/657.xz_s-2302B.champsimtrace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/cactusADM_734B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/gcc_39B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/h264ref_178B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/libquantum_1210B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/namd_400B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/tonto_422B.trace.xz | perl gen_csv.pl >> data.csv
bin/champsim --warmup_instructions 200000 --simulation_instructions 500000 benchmarks/zeusmp_300B.trace.xz | perl gen_csv.pl >> data.csv
