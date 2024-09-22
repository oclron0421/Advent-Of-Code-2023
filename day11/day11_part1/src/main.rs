use std::fs;
use std::fs::read_to_string;
use std::io;
use std::path::Path;

fn main() {
    let filename = Path::new("C:/Code Projects/Advent-Of-Code-2023/day11/day11.txt");
    let contents: String =
        fs::read_to_string(filename).expect("Something went wrong reading the file");
    println!("{contents}");
    println!("Hello, world!");
}
