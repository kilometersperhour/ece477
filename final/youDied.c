void youDied() {
    serialChatter(fd, "at10=(5,0,0,4)", roundSpeed); // Play red death animation
    serialChatter(fd, "at10=(0,0,0,8)", roundSpeed); // Fade to black
    return;
}
