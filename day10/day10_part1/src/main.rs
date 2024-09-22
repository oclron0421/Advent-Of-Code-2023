use std::env;
use std::fs;
use std::io::{self, BufRead, BufReader};
use std::path;

struct Point {
    x: i32,
    y: i32,
    pipe: char,
}

fn main() -> std::io::Result<()> {
    // Open the file for reading
    let file = fs::File::open("day10.txt")?;

    // Create a buffered reader to read the file
    let reader = BufReader::new(file);

    // Read the file line by line
    for line in reader.lines() {
        println!("{}", line?);
    }

    Ok(())
}
