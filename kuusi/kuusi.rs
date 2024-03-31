use std::env;
use rand::Rng;

const FILLERS: &'static [char] = &[
	'!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
	':', ';', '<', '=', '>', '?', '@',
	'[', '\\', ']', '^', '_', '`',
	'{', '|', '}', '~'
];

fn random_filler() -> char {
    let idx = rand::thread_rng().gen_range(0..FILLERS.len()-1);
    return FILLERS[idx]
}

fn main() {
    let args: Vec<String> = env::args().collect();

    let mut max: u16 = 50;

    if args.len() > 1 {
        max = args[1].parse::<u16>().unwrap();
    }

    for size in 0..max {

        for _pad in size..max {
            print!(" ");
        }

        for _fill in 1..size*2 {
            print!("{}", random_filler());
        }

        print!("\n");
    }
}
