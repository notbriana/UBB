from domain import Assignment


class Service:
    def __init__(self, repo):
        self._repo = repo

    def repo(self):
        return self._repo

    def add_assignment(self, id, student_name, solution):
        assignment = Assignment(id, student_name, solution)
        if assignment.get_id() in self._repo.get_all_ids():
            raise ValueError("Assignment id already exists")
        if len(assignment.get_student_name())< 3:
            raise ValueError("Student name too short")
        if len(assignment.get_solution()) == 0:
            raise ValueError("Solution too short")
        self._repo.add(assignment)

    def get_all_assignments_increasing_order(self):
        assignments = self._repo.get_all()
        assignments_sorted = sorted(assignments, key=lambda assignment: assignment.get_id())
        return assignments_sorted

    def dishonesty_check(self):
        assignments = self._repo.get_all()
        pairs = []

        for i in range(len(assignments)):
            for j in range(i + 1, len(assignments)):
                words1 = assignments[i].get_solution().split()
                words2 = assignments[j].get_solution().split()

                # Count common words
                common_count = 0
                for word in words1:
                    if word in words2:
                        common_count += 1

                # Total unique words from both lists
                total_count = len(words1) + len(words2) - common_count

                # Calculate percentage of common words
                common_percentage = common_count / total_count * 100

                if common_percentage >= 20:
                    pairs.append((assignments[i], assignments[j], common_percentage))

        return pairs

