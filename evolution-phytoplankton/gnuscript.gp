do for [iter=1:13] {

    set terminal jpeg size 1300,1300
    set output "plots/dplot_".iter.".jpeg"

    set nokey
    set notics
    set xrange [0:6.30]
    set pointsize 4

    plot "results/data_file_".iter notitle with dots

    unset output
}
