//aprendendo constantes e variaveis em RUST
//Programa em que faz a conversão de horas trabalhas para segundos numa semana.
//constante, definimos o tipo da var 

const SECONDS_IN_MINUTE: u32 = 60;
const MINUTES_IN_HOUR: u32 = 60;
const HOUR_IN_SECONDS: u32 = SECONDS_IN_MINUTE * MINUTES_IN_HOUR;


fn main() {
    let total = 30;
    let total_em_segundos = total * HOUR_IN_SECONDS;
    println!("Você trabalhou {} segundos.", total_em_segundos);
   
}