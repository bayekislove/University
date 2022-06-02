import matplotlib.pyplot as plt

left_data = [5, 4, 3, 2, 1]
right_data = [0.1, 0.2, 0.4, 0.8, 1.6]

fig, ax_left = plt.subplots()
ax_right = ax_left.twinx()

ax_left.plot(left_data, color='black')
ax_right.plot(right_data, color='red')

plt.show()