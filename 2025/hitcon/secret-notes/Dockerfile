FROM archlinux:base-20250803.0.394512

RUN sed -i 's%^Include = /etc/pacman.d/mirrorlist$%SigLevel = PackageRequired\nServer=https://archive.archlinux.org/repos/2025/08/03/$repo/os/$arch%' /etc/pacman.conf
RUN pacman -Sy --noconfirm socat

RUN useradd -m -s /bin/bash secret_notes
RUN touch /flag && chown secret_notes:secret_notes /flag
USER secret_notes
WORKDIR /home/secret_notes

EXPOSE 12387

CMD ["socat", "tcp-listen:12387,fork", "exec:/home/secret_notes/run.sh,reuseaddr"]
