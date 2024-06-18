

Test test = new TestImpl();
test.blah( (int i, LocalDate l) -> println(i + l) );
test = test.next();
test.show(5.0);
test.guess( (int i, double j) -> i + j );
test.guess( (String s) -> println(s) );
if (test.isTrue()) {
	int u = test.getFinalValue();
}


-------



interface HasId {
	String getId();
}

class User implements HasId {
	private String uniqueId;
	private int age;
	public User(String uniqueId, String name, int age) {
		this.uniqueId = uniqueId;
		this.age = age;
	}
	public String getId() { return id; }
}

record Patient(String getId, int room) implements HasId {}

class Database<T> {
	private .... // data structure of your choice to help you do the job
	public Optional<T> get(String id) { }
	public T getOrThrows(String id) { }
	public void insertOrReplace(T t) { }
	public void insertOrThrows(T t) { }
}

...
// should work
Database<User> dbUser = new Database<>();
Database<Patient> dbPatient = new Database<>();
// should not work (String doesn't implement HasId)
Database<String> dbUser = new Database<>();

------

/*
for (int i: Range.of(0, 5)) {
	...
}
*/
for (int i: Range.of(0, i -> i + 1, i -> i < 5)) {
	...
}
for (String s: Range.of("", s -> s += "a", s -> !s.equals("aaaa"))) {
	
}
for (List<Integer> ls: Range.of(new ArrayList<>(); ls -> ls.append(10), s -> s.size() < 10)) {
	
}


---