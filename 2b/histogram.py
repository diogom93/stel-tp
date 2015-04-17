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

matplotlib.pyplot.plot(scale, histogram, 'r--', linewidth = 2)
matplotlib.pyplot.bar(scale, histogram, width = 2, color = 'blue', alpha = 0.75)
matplotlib.pyplot.xlabel('Tempo')
matplotlib.pyplot.ylabel('Nº de chamadas')
matplotlib.pyplot.title('Histograma')
matplotlib.pyplot.show()