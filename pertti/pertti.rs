use std::env;
use std::io;

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut text = String::new();

    if args.len() > 1 {
        text = args[1].clone();
    } else {
        println!("Syötä teksti:");
        io::stdin().read_line(&mut text).unwrap();
    }

    let z = text.trim_end().len();

    for y in 0..z {
        for x in y..y + z {
            let chr = text.chars().nth(x % z).unwrap();
            let delim = if x - y == z - 1 { '\n' } else { ' ' };
            print!("{chr}{delim}");
        }
    }
}
