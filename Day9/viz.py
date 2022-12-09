from matplotlib import pyplot as plt

x_list = []
y_list = []
with open("output.txt") as output_data_file:
    for line in output_data_file:
        line = line.strip().split(",")
        x = []
        y = []
        for i in range(0, 20, 2):
            x.append(line[i])
        for i in range(1, 20, 2):
            y.append(line[i])
        x_list.append(x)
        y_list.append(y)

for x, y in zip(x_list, y_list):
    plt.scatter(x, y)
    plt.xlim([-20, 20])
    plt.ylim([-20, 20])
    plt.xticks(range(-20, 20))
    plt.yticks(range(-20, 20))
    plt.show()