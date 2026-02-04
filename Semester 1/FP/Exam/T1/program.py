from random import randint

# Functions section
def create_candidate(id: int, name: str, no_votes) -> dict:
    return {
        'id': id,
        'name': name,
        'no_votes': 0
    }


def get_id(candidate: dict) -> int:
    return candidate['id']


def get_name(candidate: dict) -> str:
    return candidate['name']



def get_no_votes(candidate: dict) -> int:
    return candidate['no_votes']


def inc_no_votes(candidate: dict) -> None:
    candidate['no_votes'] += 1


def validate_candidate(candidate: dict) -> bool:
    if not candidate['name']:
        return False
    if candidate['id'] <= 0:
        return False
    return True


def preexistent_dictionaries():
    return [
        create_candidate(1, "Ana", 0),
        create_candidate(2, "Banana", 0)
    ]


def is_id_unique(candidates: list, id: int) -> bool:
    for candidate in candidates:
        if candidate['id'] == id:
            return False
    return True


def validate_twice(new_candidate: list) -> bool:
    if not validate_candidate(new_candidate):
        return False

    if not is_id_unique(new_candidate, new_candidate['id']):
        return False

    return True

def add_candidate(candidates: list, command: str) -> None:
    parts = command.strip().split(' ', 1)

    id = int(parts[0])
    name = parts[1].strip()

    new_candidate = create_candidate(id, name, 0)
    if validate_twice(new_candidate):
        candidates.append(new_candidate)


def show_candidates(candidates: list) -> str:
    if len(candidates) == 0:
        return "No candidates available."

    candidate_list = ""
    for candidate in candidates:
        candidate_list += f"{candidate['id']} {candidate['name']} {candidate['no_votes']}\n"

    return candidate_list


def vote(candidates: list) -> None:
    if not candidates:
        return

    n = len(candidates)
    id_new = randint(1, n)

    for candidate in candidates:
        if get_id(candidate) == id_new:
            inc_no_votes(candidate)


def vote_tiktok(command: str):
    parts = command.strip().split(' ')

    if len(parts) < 2:
        raise ValueError("Command format is incorrect. Expected: 'tiktok vote <id> <number>'")

    try:
        id = int(parts[0])
        number = int(parts[1].strip())
    except ValueError:
        raise ValueError("ID and number must be integers.")

    return id, number

def vote_tiktok_new(candidates, command: str):
    id, number = vote_tiktok(command)
    for candidate in candidates:
        if get_id(candidate) == id:
            candidate['no_votes'] += number

def test_tiktok_vote():
    candidates = hardcoded_dict()
    initial_votes = get_no_votes(candidates[0])
    vote_tiktok_new(candidates, "tiktok vote 1 34")
    assert get_no_votes(candidates[0]) == initial_votes + 34, "Vote count did not increase"

def test_add_candidate():
    candidates = hardcoded_dict()
    add_candidate(candidates, "add candidate 3 Cherry")
    assert len(candidates) > 2, "Failed to add candidate"

def test_show_candidates():
    candidates = hardcoded_dict()
    result = show_candidates(candidates)
    assert "Ana" in result or "Banana" in result, "Candidates not found"

def test_vote():
    candidates = hardcoded_dict()
    initial_votes = get_no_votes(candidates[0])
    vote(candidates)
    assert get_no_votes(candidates[0]) == initial_votes + 1, "Vote count did not increase"


# User interface section
def main():
    candidates = preexistent_dictionaries()
    while True:
        command = input("Enter a command (add, show, vote, tiktok_vote, quit): ").strip()

        if command.startswith("add candidate"):
            add_candidate(candidates, command[14:])
            print("Candidate added")

        elif command.startswith("show candidates"):
            result = show_candidates(candidates)
            print(result)

        elif command.startswith("vote"):
            vote(candidates)

        elif command.startswith("tiktok vote"):
            vote_tiktok_new(candidates, command[12:])

        elif command == "quit":
            break
main()
