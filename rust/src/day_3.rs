use std::fs;

fn main() {
  let input: String = fs::read_to_string("../data/input3.txt")
    .expect("Failed to read file");
  let lines: Vec<Vec<i128>> = parse(&input);
  
  println!("Part 1: {}", part1(&lines));
  println!("Part 2: {}", part2(&lines));
}

fn part1(lines: &[Vec<i128>]) -> i128 {
  let mut voltage: i128 = 0;

  for line in lines {
    let (_, &lhs) = line[..line.len() - 1].iter()
      .enumerate()
      .max_by_key(|&(_, &x)|x)
      .unwrap();
    let &rhs = line.iter().skip_while(|&&x| x != lhs)
      .skip(1).max().unwrap();
    voltage += lhs * 10 + rhs;
  }
  voltage
}

fn part2(lines: &[Vec<i128>]) -> i128 {
  let powers: Vec<i128> = (0..12).map(|i| 10_i128.pow(i)).collect(); 
  let mut voltage = 0;

  for line in lines {
    let mut left = 0;
    let mut right = line.len() - 11;

    for digit in (0..12).rev() {
      let (mut max_i, mut max_v) = (0, &line[left]);
      for (i, v) in line[left..right].iter().enumerate() {
        if v > max_v {
          max_v = v;
          max_i = i;
        }
      }
      voltage += max_v * powers[digit];
      left += max_i + 1;
      right += 1;
    }
  }
  voltage
}

fn parse(input: &str) -> Vec<Vec<i128>> {
  input.lines().map(|line| {
    line.chars().filter_map(|c| c.to_digit(10))
    .map(|d| d as i128).collect()
  }).collect()
}
