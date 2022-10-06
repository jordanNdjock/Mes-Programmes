import java.util.Scanner;
import java.util.Random;
public class Main {
    public static void main(String[] args) {

        Scanner joueur = new Scanner(System.in);
        Scanner choixDif = new Scanner(System.in);
        int choix, difficult, nbAl, difficults;
        Random random = new Random();
        ListesPays tab = new ListesPays();
        System.out.println(" ---- Jeu des Capitales des Pays ---- \n");
        System.out.println("Joueur 1 : Entrer votre nom -> ");
        Player[] J = new Player[]{new Player("", 0), new Player("", 0)};
        J[0].nom = joueur.nextLine();
        System.out.println("Joueur 2 : Entrer votre nom -> ");
        J[1].nom = joueur.nextLine();
        String choixP;
        Scanner play = new Scanner(System.in);
        do {

            do {
                System.out.println("\nDifficultés de jeu");
                System.out.println("-----------------------");
                System.out.println("1 - Facile (5 pays)");
                System.out.println("2 - Medium (10 pays)");
                System.out.println("3 - Difficile (15 pays)");
                System.out.println("4 - Expert (20 pays)");
                System.out.println("------------------------");
                System.out.println("Choississez votre difficulté de jeu : ");
                choix = choixDif.nextInt();
                if (choix < 1 || choix > 4) {
                    System.out.println("Choix incorrect, entrer une valeur comprise entre 1 et 4 \n");
                }
            } while (choix < 1 || choix > 4);
            String diff;
            if(choix == 1){
                difficult = 5;
                difficults = 5;
                diff = "Facile";
            }else if(choix == 2){
                difficult = 10;
                difficults = 10;
                diff = "Medium";
            }else if(choix == 3){
                difficult = 15;
                difficults = 15;
                diff = "Difficile";
            }else{
                difficult = 20;
                difficults = 20;
                diff = "Expert";
            }
            int partie = 1, i = 0,j = 1;
            Scanner choixPays = new Scanner(System.in);
            String reponse;
            System.out.println("\nVous avez choisis la difficulté '"+diff+"'\n");
            do {
                System.out.println("Tour du joueur " + (i + 1) + "\n");
                do {
                    nbAl = random.nextInt(31);

                    System.out.println(j+" - Quelle est la capitale de ce pays ? : " + tab.Liste[nbAl].nom);
                    reponse = choixPays.nextLine();
                    if (tab.Liste[nbAl].nomCapitale.equalsIgnoreCase(reponse)) {
                        System.out.println("Bonne reponse !");
                        J[i].score++;
                    } else {
                        System.out.println("Mauvaise reponse. Il fallait repondre " + tab.Liste[nbAl].nomCapitale);
                    }
                    j++;
                    difficults--;
                } while (difficults > 0);
                System.out.println("\nC'est terminé ! << Score du joueur " + J[i].nom + " : " + J[i].score + "/" + difficult + " >>\n ");
                i++;
                partie++;





                j = 1;
                difficults = difficult;
            } while (partie < 3);
            if (J[0].score < J[1].score) {
                System.out.println("Le gagnant est le joueur : " + J[1].nom + " Bravo !");
            } else if (J[0].score > J[1].score) {
                System.out.println("Le gagnant est le joueur " + J[0].nom + " Bravo !");
            } else {
                System.out.println("Les joueurs sont à égalité !!! ");
            }

            System.out.println("\nVoulez-vous recommencer la partie ?(O/N): ");
            choixP = String.valueOf(play.nextLine().charAt(0));
            J[0].score = 0;
            J[1].score = 0;
        }while(!choixP.equalsIgnoreCase("N"));
        System.out.println("Au revoir, merci d'avoir joué !");
    }
}