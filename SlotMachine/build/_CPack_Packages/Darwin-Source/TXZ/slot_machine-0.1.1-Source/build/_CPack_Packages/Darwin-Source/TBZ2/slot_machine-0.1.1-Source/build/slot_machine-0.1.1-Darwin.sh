#!/bin/sh

# Display usage
cpack_usage()
{
  cat <<EOF
Usage: $0 [options]
Options: [defaults in brackets after descriptions]
  --help            print this message
  --version         print cmake installer version
  --prefix=dir      directory in which to install
  --include-subdir  include the slot_machine-0.1.1-Darwin subdirectory
  --exclude-subdir  exclude the slot_machine-0.1.1-Darwin subdirectory
  --skip-license    accept license
EOF
  exit 1
}

cpack_echo_exit()
{
  echo $1
  exit 1
}

# Display version
cpack_version()
{
  echo "slot_machine Installer Version: 0.1.1, Copyright (c) Humanity"
}

# Helper function to fix windows paths.
cpack_fix_slashes ()
{
  echo "$1" | sed 's/\\/\//g'
}

interactive=TRUE
cpack_skip_license=FALSE
cpack_include_subdir=""
for a in "$@"; do
  if echo $a | grep "^--prefix=" > /dev/null 2> /dev/null; then
    cpack_prefix_dir=`echo $a | sed "s/^--prefix=//"`
    cpack_prefix_dir=`cpack_fix_slashes "${cpack_prefix_dir}"`
  fi
  if echo $a | grep "^--help" > /dev/null 2> /dev/null; then
    cpack_usage 
  fi
  if echo $a | grep "^--version" > /dev/null 2> /dev/null; then
    cpack_version 
    exit 2
  fi
  if echo $a | grep "^--include-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=TRUE
  fi
  if echo $a | grep "^--exclude-subdir" > /dev/null 2> /dev/null; then
    cpack_include_subdir=FALSE
  fi
  if echo $a | grep "^--skip-license" > /dev/null 2> /dev/null; then
    cpack_skip_license=TRUE
  fi
done

if [ "x${cpack_include_subdir}x" != "xx" -o "x${cpack_skip_license}x" = "xTRUEx" ]
then
  interactive=FALSE
fi

cpack_version
echo "This is a self-extracting archive."
toplevel="`pwd`"
if [ "x${cpack_prefix_dir}x" != "xx" ]
then
  toplevel="${cpack_prefix_dir}"
fi

echo "The archive will be extracted to: ${toplevel}"

if [ "x${interactive}x" = "xTRUEx" ]
then
  echo ""
  echo "If you want to stop extracting, please press <ctrl-C>."

  if [ "x${cpack_skip_license}x" != "xTRUEx" ]
  then
    more << '____cpack__here_doc____'

____cpack__here_doc____
    echo
    echo "Do you accept the license? [yN]: "
    read line leftover
    case ${line} in
      y* | Y*)
        cpack_license_accepted=TRUE;;
      *)
        echo "License not accepted. Exiting ..."
        exit 1;;
    esac
  fi

  if [ "x${cpack_include_subdir}x" = "xx" ]
  then
    echo "By default the slot_machine will be installed in:"
    echo "  \"${toplevel}/slot_machine-0.1.1-Darwin\""
    echo "Do you want to include the subdirectory slot_machine-0.1.1-Darwin?"
    echo "Saying no will install in: \"${toplevel}\" [Yn]: "
    read line leftover
    cpack_include_subdir=TRUE
    case ${line} in
      n* | N*)
        cpack_include_subdir=FALSE
    esac
  fi
fi

if [ "x${cpack_include_subdir}x" = "xTRUEx" ]
then
  toplevel="${toplevel}/slot_machine-0.1.1-Darwin"
  mkdir -p "${toplevel}"
fi
echo
echo "Using target directory: ${toplevel}"
echo "Extracting, please wait..."
echo ""

# take the archive portion of this file and pipe it to tar
# the NUMERIC parameter in this command should be one more
# than the number of lines in this header file
# there are tails which don't understand the "-n" argument, e.g. on SunOS
# OTOH there are tails which complain when not using the "-n" argument (e.g. GNU)
# so at first try to tail some file to see if tail fails if used with "-n"
# if so, don't use "-n"
use_new_tail_syntax="-n"
tail $use_new_tail_syntax +1 "$0" > /dev/null 2> /dev/null || use_new_tail_syntax=""

extractor="pax -r"
command -v pax > /dev/null 2> /dev/null || extractor="tar xf -"

tail $use_new_tail_syntax +147 "$0" | gunzip | (cd "${toplevel}" && ${extractor}) || cpack_echo_exit "Problem unpacking the slot_machine-0.1.1-Darwin"

echo "Unpacking finished successfully"

exit 0
#-----------------------------------------------------------
#      Start of TAR.GZ file
#-----------------------------------------------------------;

� �
�\ �_hE��.w5�����Վ����^�_(Rrڥ�&mz)A�q�n�n�n��?�<�A0��=�(B��>(�Q��>�/E*���I�B�S��9�;��msi-����f�����o/��ݒ�'�.#IR.��n��ji$���L�ӹ����PJ�dGR fv;0�cيIB�kJ��v�qd��n��ֱQ�'�H���a��R�i:ލ9���$=��*'�H�3#)	@i7������?���! } ,�}���� |���$)R:�?)�%OOݭ��<T�Z���������l��8l<�%ɯ�|�����C�n,�&B�픬�z�{z>�C?��ץ�j����z��(g���l٦�W{����9�'�mG�P�+H�Uc�/�^���<4��n^O�y��}�nڀ�i^�X����Țo��:j�fO�(g�q��|kE�j�]v�^���s�_��o�+��7�oȧ׹�;l~�&�'O�'�;9�|����:��w�|o%6���_�pq����e�t��HiI��^��rtd%z�.y1�yx���M±�D]+%*��
���q���G󿧥���_$�w�v��?BD"�n+(/��R?����2M�>�ݲ17)z�1-l�3�t����v�f�ˉ�I�_��V�f��+Ǔ��?O��_B����-7������	����n��?G�@ �@ �@ �{3SX���xS�V�Cͥ�K�������Y�PX��L������1�r�� �F��za9z	��xî�ݏ�r���gH��%�:�>�"P�%��ڄ;������{ޟz��ɘ[���[�Q�q�kj� ������Oy�n���e�Na���7�v�*ij�~r�6���W�ʟk�.��U��k����=�Y�N�b<�MK3t��c����*>I��4J،�bC�G114Æ�
cU�Y�3B%����kz�D����+��Y0��g��3�yz������X=���}�@ �@ �_���cc�>�^1�	Κ��}X�{����l���6#���PlC��k�ij�MM� aD��s���հBe�k(�b�Ǌ>��޹�̓�_������\�!�}��}��>;��� �`�b��6��"7^nw�eo,��}����rݩ�]}쟿��"���������J�a�V����9�~d����O���_Y��W6�����k���;&�@�ik�nAE�@۶�W-�&,:�ajJ=�|���!�� :/O���D��oNMC���'ɠd�^�@ <��eC�� @  