import csv
import matplotlib.pyplot as plot
import numpy 

with open('output.csv', 'r') as output:
	histogram = numpy.loadtxt(output, delimiter = ',', dtype = "int")
			
plot.bar(range(0,20), histogram, alpha = 0.75)
plot.xlabel('Tempo')
plot.ylabel('Nº de chamadas')
plot.title('Histograma do intervalo entre chegada de chamadas')

plot.show()