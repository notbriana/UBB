import pickle

# Defines the file paths
file_paths = ["students.pickle", "disciplines.pickle", "grades.pickle"]

# Creates empty pickle files
for file_path in file_paths:
    with open(file_path, "wb") as f:
        pickle.dump([], f)

print("Empty pickle files created.")
