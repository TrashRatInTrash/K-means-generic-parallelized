
import csv
import random

def generate_points(num_points):
    points = []
    for _ in range(num_points):
        x = random.randint(-1000, 1000)
        y = random.randint(-1000, 1000)
        points.append((x, y))
    return points

def write_to_csv(filename, points):
    with open(filename, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerows(points)  # Writing the points

if __name__ == "__main__":
    num_points = int(input("Enter the number of points to generate: "))
    filename = "points.csv"
    
    points = generate_points(num_points)
    write_to_csv(filename, points)
    
    print(f"{num_points} points have been written to {filename}.")
