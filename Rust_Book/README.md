# Official Rust Book

### Creating new project with cargo
 
- Cargo new hello_cargo
 
### Building and running a cargo project
- Cargo build
- It creates an executable
- To build and run use "cargo run"
- To check compilation and doesn’t generate executable "cargo check"
 
### Building for release
- Cargo build --release (compiles with optimizations)


### Rust variables :
- Default variables are immutable
- Adding mut makes the var mutable (ie. let mut x = 5 ; )
- Const are always immutable and declared by const keyword
- ``` const THREE_HOURS_IN_SECONDS: u32 = 60 * 60 * 3; ```
- Shadowing is declaring a new variable with the same name as previous variable, first variable is shadowed by the second until the code ends .\

```
fn main() {
	let x = 5;
 
	let x = x + 1;
 
	{
    	let x = x * 2;
    	println!("The value of x in the inner scope is: {x}");
	}
 
	println!("The value of x is: {x}");
}
```
- Note that mutability and shadowing are different

## Ownership : 
- Ownership is set of rules that govern how rust manages memory.
- Some languages have garbage collection that regularly looks for no-longer used memory ,in other languages programmer must manually allocate and free memory. 
- In Rust , Memory is managed through a system of ownership with a set of rules that the compiler checks , If any of the rules are violated then program wont compile . 
- Stack and the Heap are parts of memory available to your code to use at runtime but are structured in different ways . 
- Stack is LIFO and all the data is of fixed known size , if data with unknown size at compile time or size might change then it must be stored in the heap instead 
- When you put data on the heap you request a certain amount of space , Memory allocator finds an empty spot in the heap that is big enough and marks it as in use and returns a pointer . 
- When code calls a the function the values passed into the function and function local variables get pushed onto the stack , when function is over they get popped off the stack. 
- Keeping track of what parts of code are using what data on the headp and minimizing the mount of duplicate data on the heap so you dont run out of space are all problem that rust ownership addresses . 
- Main purpose of ownership is to manage heap data , it helps explaining why rust ownership works the way it does . 

## Ownership Rules : 
- Each value in rust has a owner 
- There can be only one owner at a time 
- When the owner goes out of shape the value will be dropped 

### Variable Scope : 
- When a variable somes in scope its valid , it remains valid until it goes out of scope
- String data is stored in heap so the example her is to explore how rust knows when to clean up that data 
- Strings are by default immutable but when there is user input there is second type called `String` , you can create a String from a string literal using the from function
           
    let s = String::from(“hello”);
- :: operator allows us to namespace this particular from function under the String .

### Memory and Allocation 
- In case of string literal we know the contents at compile time , so the text is hardcoded directly into final executable 
- String type is mutable , growing piece of text we need to allocate an amount of memory on the heap unknown at compile time . 
- String::from implementation requests the memory it needs 
- In Rust memory is automatically returned once the variable that owns it goes out of scope 
- When a variable goes out of scope , Rust calls a special function drop , Rust calls drop automatically at the closing curly bracket 

### Ways Variables and Data Interact: Move
```
fn main() {
    let x = 5;
    let y = x;
}
```

In the example above , bind the value 5 to x; then make a copy of the value in x and bind it to y.” We now have two variables, x and y, and both equal 5

```
fn main() {
    let s1 = String::from("hello");
    let s2 = s1;
}
```

In the example above , the behaviour is different : When we assign s1 to s2 , the String data is copied , meaning we copy the pointer , the length and capacity that are on the stack. 

- Rust doesnt copy the heap data otherwise this could be very expensive runtime operation if heap data is huge 
- When s2 and s1 go out of scope , they will both try to free the same memory. This is known as double free error and is one of the memory safety bugs , Freeing memory twice can lead to memory corruption . 
```
fn main() {
    let s1 = String::from("hello");
    let s2 = s1;

    println!("{}, world!", s1);
}
```

- The above program returns an error , as after the line let s2=s1 , Rust considers s1 as no longer valid. Therefore rust doesnt need to free anything when s1 goes out of scope .
- This is kind of a shallow copy , Rust will never automatically create a deep copy of the data .  

### Ways Variables and Data interact : Clone 
If we want to deeply copy the heap data , not just the stack data then we can use a method called clone 
```
fn main() {
    let s1 = String::from("hello");
    let s2 = s1.clone();

    println!("s1 = {}, s2 = {}", s1, s2);
}
```



### Stack-Only Data : Copy 
```
fn main() {
    let x = 5;
    let y = x;

    println!("x = {}, y = {}", x, y);
}
```

- The above code works without calling clone cause the size of integer is known at compile time and stored entirely on stack , so copies of actual values are quick to make . 

Here are some of the types that implement Copy:
- All the integer types, such as u32.
- The Boolean type, bool, with values true and false.
- All the floating point types, such as f64.
- The character type, char.
- Tuples, if they only contain types that also implement Copy. For example, (i32, i32) implements Copy, but (i32, String) does not.



## Ownership and Functions 
```
fn main() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(s);             // s's value moves into the function...
                                    // ... and so is no longer valid here

    let x = 5;                      // x comes into scope

    makes_copy(x);                  // x would move into the function,
                                    // but i32 is Copy, so it's okay to still
                                    // use x afterward

} // Here, x goes out of scope, then s. But because s's value was moved, nothing
  // special happens.

fn takes_ownership(some_string: String) { // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) { // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.
```

If we tried to use s after the call to takes_ownership, Rust would throw a compile-time error. 
But this is too much imo. Book mentions “Rust has a feature for using a value without transferring ownership, called references.”

### References and Borrowing 
A Reference is like a pointer in that its an address we can follow to access the data stored at that address. 
Unlike a pointer , A reference is guaranteed to point to a valid value of a particular type for the life of that reference. 
```
fn main() {
    let s1 = String::from("hello");

    let len = calculate_length(&s1);

    println!("The length of '{}' is {}.", s1, len);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}
```

By default references are immutable , it needs to be explicitly specified as mutable to edit the reference . 

```
fn main() {
    let mut s = String::from("hello");

    change(&mut s);
}

fn change(some_string: &mut String) {
    some_string.push_str(", world");
}
```

- When functions have references as parameters instead of actual values , we wont need to return the values in order to give back ownership , because we never had ownership
- Mutable references have one big restriction: if you have a mutable reference to a value, you can have no other references to that value
- Rust refuses to compile code with data races . 
- We can use curly brackets to create a new scope , allowing for multiple mutable references just not simultaneous ones 
- You cant combine mutable and non mutable references in a single scope 

### Dangling References 
- In languages with pointers its easy to erroneously create a dangling pointer , A pointer that references a location in memory taht may have been given to someone else , by freeing some memory while preserving the pointer to that memory . 
- Rust compiler guarantees that references will never be dangling references .

### Rules of references : 
- At any given time , you can have wither one mutable reference or any number of immutable references. 
- References must always be valid 

### Slice Type 
- Slice let you reference a contiguous sequence of elements in a collection rather than the whole collection . 
- A slice is kind of a reference so it doesnt have ownership . 

String slice : 

```
fn main() {
    let s = String::from("hello world");

    let hello = &s[0..5];
    let world = &s[6..11];
}
```

## Structs 
- Custom data type that lets you package together and name multiple related values that make up a meaningful group. 
- Structs are similar to tuples but you need name ach piece of data so its clear what the values mean . 
```
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}
```

## Ownership and Functions  

```
fn main() {
    let s = String::from("hello");  // s comes into scope

    takes_ownership(s);             // s's value moves into the function...
                                    // ... and so is no longer valid here

    let x = 5;                      // x comes into scope

    makes_copy(x);                  // x would move into the function,
                                    // but i32 is Copy, so it's okay to still
                                    // use x afterward

} // Here, x goes out of scope, then s. But because s's value was moved, nothing
  // special happens.

fn takes_ownership(some_string: String) { // some_string comes into scope
    println!("{}", some_string);
} // Here, some_string goes out of scope and `drop` is called. The backing
  // memory is freed.

fn makes_copy(some_integer: i32) { // some_integer comes into scope
    println!("{}", some_integer);
} // Here, some_integer goes out of scope. Nothing special happens.
```

- If we tried to use s after the call to takes_ownership, Rust would throw a compile-time error. 
- But this is too much imo. Book mentions “Rust has a feature for using a value without transferring ownership, called references.”

### References and Borrowing 
- A Reference is like a pointer in that its an address we can follow to access the data stored at that address. 
- Unlike a pointer , A reference is guaranteed to point to a valid value of a particular type for the life of that reference. 
```
fn main() {
    let s1 = String::from("hello");

    let len = calculate_length(&s1);

    println!("The length of '{}' is {}.", s1, len);
}

fn calculate_length(s: &String) -> usize {
    s.len()
}
```


By default references are immutable , it needs to be explicitly specified as mutable to edit the reference . 

```
fn main() {
    let mut s = String::from("hello");

    change(&mut s);
}

fn change(some_string: &mut String) {
    some_string.push_str(", world");
}
```

- When functions have references as parameters instead of actual values , we wont need to return the values in order to give back ownership , because we never had ownership
- Mutable references have one big restriction: if you have a mutable reference to a value, you can have no other references to that value
- Rust refuses to compile code with data races . 
- We can use curly brackets to create a new scope , allowing for multiple mutable references just not simultaneous ones 
- You cant combine mutable and non mutable references in a single scope 

### Dangling References 
- In languages with pointers its easy to erroneously create a dangling pointer , A pointer that references a location in memory taht may have been given to someone else , by freeing some memory while preserving the pointer to that memory . 
- Rust compiler guarantees that references will never be dangling references .

### Rules of references : 
- At any given time , you can have wither one mutable reference or any number of immutable references. 
- References must always be valid 

### Slice Type 
- Slice let you reference a contiguous sequence of elements in a collection rather than the whole collection . 
- A slice is kind of a reference so it doesnt have ownership . 
String slice : 

```
fn main() {
    let s = String::from("hello world");

    let hello = &s[0..5];
    let world = &s[6..11];
}
```

### Structs 
- Custom data type that lets you package together and name multiple related values that make up a meaningful group. 
- Structs are similar to tuples but you need name each piece of data so its clear what the values mean . 

```
struct User {
    active: bool,
    username: String,
    email: String,
    sign_in_count: u64,
}

fn main() {
    let mut user1 = User {
        active: true,
        username: String::from("someusername123"),
        email: String::from("someone@example.com"),
        sign_in_count: 1,
    };
    user1.email = String::from("anotheremail@example.com");
}
```
- Note that the entire instance must be mutable; Rust doesn’t allow us to mark only certain fields as mutable

### Creating instances from other instances with Struct Update Syntax 
- Its often useful to create a new instance of struct that includes most of the values from another instance but changes some , we can use struct update syntax.
```
fn main() {
    // --snip--

    let user2 = User {
        email: String::from("another@example.com"),
        ..user1
    };
}
```
- Here syntax `..` specifies that remaining fields not explicitly set should have same value as the fields in the given instance. 

### Tuple structs without named fields to create different types 
- Tuples dont have names associated with their fields but rather they just have types of the fields.
```
struct Color(i32, i32, i32);
struct Point(i32, i32, i32);

fn main() {
    let black = Color(0, 0, 0);
    let origin = Point(0, 0, 0);
}

```




