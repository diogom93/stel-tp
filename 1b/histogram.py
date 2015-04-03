import csv
import matplotlib.pyplot
import numpy

scale = []
histogram = []

with open('output.csv') as f:
	reader = csv.reader(f, delimiter = ';')
	for row in reader:
		scale.append(float(row[0]))
		histogram.append(int(row[1]))
		
x = [i for i in numpy.arange(0.05, 1.5, 0.05)]

cenas = []

for i in x:
	cenas.append(1000000*8*numpy.exp(-8*i*1.5))

matplotlib.pyplot.plot(x, cenas, 'b--', linewidth = 2.5)

matplotlib.pyplot.bar(scale, histogram, width = 0.05, color = 'green', alpha = 0.75)
matplotlib.pyplot.plot(scale, histogram, 'r--', linewidth = 2.5)
matplotlib.pyplot.xlabel('Tempo')
matplotlib.pyplot.ylabel('Nº de chamadas')
matplotlib.pyplot.title('Histograma')
matplotlib.pyplot.show()